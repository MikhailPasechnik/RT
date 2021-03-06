#include "rt.hcl"

t_color monte_carlo(t_cam camera, t_options options, t_ray ray, __global t_obj *objects, __global t_light *lights, __global uchar* tx_b, __global t_tx_info* txi_b, unsigned int *seed0, unsigned int *seed1)
{
	int		d;
	t_hit	hit;
	t_color result = (t_color)(0.0f, 0.0f, 0.0f);
	t_color mask = (t_color)(1.0f, 1.0f, 1.0f);

	d = 0;
	while (d < 10)
	{
		if (intersect(objects, options.obj_count, &ray, &hit, tx_b, txi_b) == -1)
			return result += mask * (camera.sky != -1 ? sample_sky(ray.d, tx_b, txi_b[camera.sky]) : options.background_color);

		float rand1 = 2.0f * M_PI * get_random(seed0, seed1);
		float rand2 = get_random(seed0, seed1);
		float rand2s = sqrt(rand2);

		t_vec3 N = hit.n;
		t_vec3 tmp = fabs(N.x) > 0.1f ? (t_vec3)(0.0f, 1.0f, 0.0f) : (t_vec3)(1.0f, 0.0f, 0.0f);
		t_vec3 B = normalize(cross(tmp, N));
		t_vec3 T = cross(N, B);

		result += mask * get_direct_illumination(options, hit, ray, objects, lights, tx_b, txi_b);

		mask *= hit.diff;
		ray.d = normalize(B * cos(rand1)*rand2s + T*sin(rand1)*rand2s + N*sqrt(1.0f - rand2));
		ray.o = hit.p + hit.n * 0.0001f;

		mask *= dot(ray.d, hit.n);
		d++;
	}
	return (result);
}

__kernel void k_render(
    t_options options,
    t_cam camera,
    __global t_obj* objects,
    __global t_light* lights,
    __global t_int* color_buffer,
    __global t_int* index_buffer,
    __global float3* normal_buffer,
    __global float* depth_buffer,
    __global uchar* tx_b,
    __global t_tx_info* txi_b,
    __global uint2* seed_buffer,
    __global float3* mc_buffer,
	__global float2* uv_buffer
)
{
    t_int   obj_index;

    t_ray   camera_ray;
    t_hit   camera_hit;

    t_color color;
    float3 normal_color;
    float depth_color;
    t_color refl_color;
	t_color sepia_color;

    t_int   dpth = 0;
    t_ray   refl_ray;
    t_hit   refl_hit;
    
    normal_color = (float3){0, 0, 0};
    depth_color = 99999;
    color = COLOR(0,0,0,1);
    t_color r_col[REF_DEPTH_MAX + 1];
    t_real  r_coef[REF_DEPTH_MAX + 1];

    int id = get_global_id(0);
    camera_ray = new_camera_ray(&options, &camera,
        (uint2){id % options.width, id / options.height});
	obj_index = intersect(objects, options.obj_count, &camera_ray, &camera_hit, tx_b, txi_b);
    if (options.mc)
	{
		float3 sampled_color = options.current_sample == 0 ? (float3)(0.0f, 0.0f, 0.0f) : mc_buffer[id];
		float inv_samples = 1.0f / options.target_samples;
		unsigned int seed0 = options.current_sample == 0 ? id % options.width : seed_buffer[id].x;
		unsigned int seed1 = options.current_sample == 0 ? id / options.width : seed_buffer[id].y;

		for (int i = 0; i < options.sample_step; i++)
			sampled_color += monte_carlo(camera, options, camera_ray, objects, lights, tx_b, txi_b, &seed0, &seed1) * inv_samples;

		index_buffer[id] = obj_index;
		normal_buffer[id] = camera_hit.n;

		mc_buffer[id] = sampled_color;
		color_buffer[id] = pack_color(&sampled_color);
		depth_buffer[id] = length(distance(camera_hit.p, VEC(camera.mtx.sC, camera.mtx.sD, camera.mtx.sE)));
		seed_buffer[id] = (uint2){seed0, seed1};
		uv_buffer[id] = obj_index != -1 ? camera_hit.uv : (float2){0,0};
    	return ;
	}

    if (obj_index != -1)
    {
        depth_color = length(distance(camera_hit.p, VEC(camera.mtx.sC, camera.mtx.sD, camera.mtx.sE)));
        normal_color = camera_hit.n;
        color = calc_color(options, objects, lights, id, camera_hit, camera_ray, color, tx_b, txi_b);
        
        r_col[0] = color;
        r_coef[0] = camera_hit.reflection;
        t_int c = 1;
    
        if (camera_hit.reflection != 0)
        {
            refl_ray = camera_ray;
            refl_hit = camera_hit;

            while (++dpth <= options.ref_depth)
            {
                c++;
                if ((intersect(objects, options.obj_count, &refl_ray, &refl_hit, tx_b, txi_b)) != -1) // &camera_ray - прозрачность
                {
                    refl_ray.d = normalize(reflect(-refl_ray.d, refl_hit.n));
                    refl_ray.o = (refl_ray.d * refl_hit.n < 0) ? refl_hit.p - refl_hit.n * 0.001f :
                        refl_hit.p + refl_hit.n * 0.001f;
                    r_col[dpth] = calc_color(options, objects, lights, id, refl_hit, refl_ray, refl_color, tx_b, txi_b);
                    if (!refl_hit.reflection)
                        break ;
                    r_coef[dpth] = refl_hit.reflection;
                }
                else
                {
                    r_col[dpth] = camera.sky != -1 ? sample_sky(refl_ray.d, tx_b, txi_b[camera.sky]) : options.background_color;
                    break ;
                }
            }
            if (c > 0)
            {
                r_coef[--c] = 0;
                while (--c >= 0)
                {
                    r_col[c] = coef_color(r_col[c], 1 - clamp(r_coef[c], 0.0f, 1.0f))
                        + coef_color(r_col[c + 1], clamp(r_coef[c], 0.0f, 1.0f));
                }
            }
        }
        color = r_col[0];
    }
    else
        color = camera.sky != -1 ? sample_sky(camera_ray.d, tx_b, txi_b[camera.sky]) : options.background_color;

    index_buffer[id] = obj_index;
    normal_buffer[id] = normal_color;
	color_buffer[id] = pack_color(&color);
    depth_buffer[id] = depth_color;
    uv_buffer[id] = obj_index != -1 ? camera_hit.uv : (float2){0, 0};
}





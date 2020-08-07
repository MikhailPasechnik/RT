#include "rt.hcl"

__kernel void k_render(
    t_options options,
    t_cam camera,
    __global t_obj* objects,
    __global t_light* lights,
    __global t_int* color_buffer,
    __global t_int* index_buffer,
    __global t_int* normal_buffer,
    __global t_int* depth_buffer,
    __global uchar* tx_b,
    __global t_tx_info* txi_b
)
{
    t_int   obj_index;

    t_ray   camera_ray;
    t_hit   camera_hit;

    t_color color;
    t_color normal_color;
    t_color depth_color;
    t_color refl_color;
	t_color sepia_color;

    t_int   dpth = 0;
    t_ray   refl_ray;
    t_hit   refl_hit;
    
    normal_color = COLOR(0,0,0,1);
    depth_color = COLOR(0,0,0,1);
    color = COLOR(0,0,0,1);
    t_color r_col[REF_DEPTH_MAX + 1];
    t_real  r_coef[REF_DEPTH_MAX + 1];

    int id = get_global_id(0);
    camera_ray = new_camera_ray(&options, &camera,
        (uint2){id % options.width, id / options.height});
    obj_index = intersect(objects, options.obj_count, &camera_ray, &camera_hit, tx_b, txi_b);

    if (obj_index != -1)
    {
        depth_color = distance(camera_hit.p, VEC(camera.mtx.sC,
            camera.mtx.sD, camera.mtx.sE)) / 50.0f;
        normal_color = ((camera_hit.n * -1) + 1) / 2;
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
                    r_col[dpth] = options.background_color;
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
        color = options.background_color;

    index_buffer[id] = obj_index;
    normal_buffer[id] = pack_color(&normal_color);

	color_buffer[id] = pack_color(&color);
    depth_buffer[id] = pack_color(&depth_color);
    if (options.sepia)
		color = sepia_effect(color);
    color_buffer[id] = pack_color(&color);
}

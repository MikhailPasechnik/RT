#include "rt.hcl"

t_color coef_color(t_color color, t_real coef)
{
    color.x *= coef;
	color.y *= coef;
	color.z *= coef;

	color.x = color.x > 1 ? 1 : color.x;
	color.y = color.y > 1 ? 1 : color.y;
	color.z = color.z > 1 ? 1 : color.z;
    return (color);
}

t_color calc_color(
    t_options options,
    __global t_obj* objects,
    __global t_light* lights,
    int id,
    t_hit camera_hit,
    t_ray camera_ray,
    t_color color,
	__global uchar* tx_b,
	__global t_tx_info* txi_b
)
{
    t_ray   shadow_ray;
    t_hit   shadow_hit;
    t_vec3  light_dir;

    t_vec3  ref;
    t_real  d;

    t_uint i = 0;
    t_color diffuse = COLOR(0,0,0,1);
    t_color specular = COLOR(0,0,0,1);

    while (i < options.light_count)
    {
        if (lights[i].id == ID_DIRECT || lights[i].id == ID_POINT)
        {
            light_dir = (lights[i].id == ID_DIRECT) ? dir_from_rot(lights[i].rot)
                : normalize(camera_hit.p - lights[i].pos);
            shadow_ray.o = camera_hit.p + camera_hit.n * 0.001f;
            shadow_ray.d = -light_dir;
            d = 2 * clamp(1.0f / native_sqrt(native_sqrt(dot(camera_ray.d, camera_ray.d))), 0.0f, 1.0f);
            ref = reflect(light_dir, -camera_hit.n);
            if (!(intersect(objects, options.obj_count, &shadow_ray, &shadow_hit, tx_b, txi_b) != -1))
            {
                specular += coef_color(lights[i].color * 
                    clamp(0.0f, native_powr(dot(ref, camera_ray.d), 30.0f) * d, lights[i].intensity),
                    clamp(0.0f, camera_hit.specular, 1.0f));
                diffuse += camera_hit.diff * lights[i].intensity *
                    lights[i].color * clamp(dot(camera_hit.n, shadow_ray.d), 0.0f, 1.0f);
            }
        }
        else if (lights[i].id == ID_AMB)
            diffuse += camera_hit.diff * lights[i].intensity * lights[i].color;
        i++;
        color = diffuse * 1.5f + specular;
    }
    return (color);
}


t_color			sample_texture(float2 uv, __global uchar* tx_b, t_tx_info tx_info)
{
	int				i;
	int				j;
	int				pix;
	t_color			color;
	__global uchar*	tx;

	i = clamp(0, (int)((  uv.x)*(tx_info.w)), tx_info.w - 1);
	j = clamp(0, (int)((1-uv.y)*(tx_info.h) - 0.001f), tx_info.h - 1);
	tx = &tx_b[tx_info.buffer_offset + (i + j * tx_info.w) * 4];
	return COLOR((float)tx[0] / 255, (float)tx[1] / 255, (float)tx[2] / 255, 0);
}

t_color			sepia_effect(t_color color)
{
	return COLOR(
		(color.x * .393) + (color.y *.769) + (color.z * .189),
		(color.x * .349) + (color.y *.686) + (color.z * .168),
		(color.x * .272) + (color.y *.534) + (color.z * .131), 0
	);
}

t_color sample_sky(t_vec3 vec, __global uchar* tx_b, t_tx_info txi_b)
{
	t_mat4 m;

	m4_identity(&m);
	m4_set_rotation(&m, (t_vec3){90, 0, 0});
	vec = m4_mul_vec3(&m, &vec);
	return sample_texture(get_sphere_uv(vec), tx_b, txi_b);
}

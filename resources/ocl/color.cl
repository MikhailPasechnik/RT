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
    t_color color)
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
            if (!(intersect(objects, options.obj_count, &shadow_ray, &shadow_hit) != -1))
            {
                specular += coef_color(lights[i].color * 
                    clamp(0.0f, native_powr(dot(ref, camera_ray.d), 30.0f) * d, lights[i].intensity),
                    clamp(0.0f, camera_hit.obj->mat.specular, 1.0f));
                diffuse += camera_hit.obj->mat.diff * lights[i].intensity *
                    lights[i].color * clamp(dot(camera_hit.n, shadow_ray.d), 0.0f, 1.0f);
            }
        }
        else if (lights[i].id == ID_AMB)
            diffuse += camera_hit.obj->mat.diff * lights[i].intensity * lights[i].color;
        i++;
        color = diffuse * 1.5f + specular;
    }
    return (color);
}

#include "rt.hcl"

static void col_coef(t_color color, t_real coef, t_int size)
{
	t_int i;

	i = -1;
	while (++i < size)
	    color[i] *= coef;
}

static t_color calc_color(
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
//                specular += lights[i].intensity * lights[i].color *
//                    clamp(native_powr(dot(ref, camera_ray.d), 30.0f) * d, 0.0f, 1.0f);
                specular += lights[i].color * clamp(0.0f, native_powr(dot(ref, camera_ray.d), 30.0f) * d, lights[i].intensity);
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

__kernel void k_render(
    t_options options,
    t_cam camera,
    __global t_obj* objects,
    __global t_light* lights,
    __global t_int* color_buffer,
    __global t_int* index_buffer,
    __global t_int* normal_buffer,
    __global t_int* depth_buffer
)
{
    t_int   obj_index;

    t_ray   camera_ray;
    t_hit   camera_hit;

    t_color color;
    t_color normal_color;
    t_color depth_color;

    t_ray   refl_ray;
    t_hit   refl_hit;
    t_color refl_color;
    
    normal_color = COLOR(0,0,0,1);
    depth_color = COLOR(0,0,0,1);
    color = COLOR(0,0,0,1);
    refl_color = COLOR(0,0,0,1);

    int id = get_global_id(0);
    camera_ray = new_camera_ray(&options, &camera,
        (uint2){id % options.width, id / options.height});
    obj_index = intersect(objects, options.obj_count, &camera_ray, &camera_hit);

    if (obj_index != -1)
    {
        depth_color = distance(camera_hit.p, VEC(camera.mtx.sC,
            camera.mtx.sD, camera.mtx.sE)) / 50.0f;
        normal_color = ((camera_hit.n * -1) + 1) / 2;
        color = calc_color(options, objects, lights, id, camera_hit, camera_ray, color);
        
        t_uint o = 0;
        options.depth = 0;
        refl_ray = camera_ray;
        while (o < options.obj_count && options.depth <= 1)
        {
            if ((refl_intr(objects, options.obj_count, &refl_ray, &refl_hit, o)) != -1) // &camera_ray - прозрачность
            {
                refl_ray.d = normalize(reflect(VEC(camera.mtx.sC,
                    camera.mtx.sD, camera.mtx.sE), -refl_hit.n));
                refl_ray.o = (refl_ray.d * refl_hit.n < 0) ? refl_hit.p - refl_hit.n * 0.001f :
                    refl_hit.p + refl_hit.n * 0.001f;
                refl_color = calc_color(options, objects, lights, id, refl_hit, camera_ray, refl_color);
//              col_coef(refl_color, objects[o].mat.reflection, 3);
            }
            else
                refl_color = options.background_color;
            o++;
            options.depth += 1;
        }
        color = calc_color(options, objects, lights, id, camera_hit, camera_ray, color);
    }
    else
        color = options.background_color;
    
    color += refl_color;
    index_buffer[id] = obj_index;
    normal_buffer[id] = pack_color(&normal_color);
    depth_buffer[id] = pack_color(&depth_color);
    color_buffer[id] = pack_color(&color);
}

#include "rt.hcl"

void	antialiasing()
{
	int nx = 200;
	int ny = 100;
	int ns = 100;

	camera cam;

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 col(0,0,0);
			for (int s = 0; s < ns; s++)
			{
				float u = float(i + drand48())/float(nx); // 0~1
				float v = float(j + drand48())/float(ny);
				ray r = cam.get_ray(u,v);
				col += color(r);
			}
			col /= float(ns);

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
		}
	}
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
    t_color refl_color;
	t_color sepia_color;

    t_int   dpth = -1;
    t_ray   refl_ray;
    t_hit   refl_hit;
    
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
    
        if (camera_hit.obj->mat.reflection != 0) // зеркальность start
        {
            refl_ray = camera_ray;
            refl_hit = camera_hit;

            while (++dpth <= DEPTH)
            {
                if ((intersect(objects, options.obj_count, &refl_ray, &refl_hit)) != -1) // &camera_ray - прозрачность
                {
                    refl_ray.d = normalize(reflect(-refl_ray.d, refl_hit.n));
                    refl_ray.o = (refl_ray.d * refl_hit.n < 0) ? refl_hit.p - refl_hit.n * 0.001f :
                        refl_hit.p + refl_hit.n * 0.001f;
                    refl_color += coef_color(calc_color(options, objects, lights, id, refl_hit, camera_ray, refl_color),
                        clamp(0.0f, camera_hit.obj->mat.reflection, 1.0f));
                    if (!refl_hit.obj->mat.reflection)
                        break ;
                 }
                 else
                    refl_color = coef_color(options.background_color, clamp(0.0f, camera_hit.obj->mat.reflection, 1.0f));
            }
            color += refl_color;
        }
    }
    else
        color = options.background_color;

    index_buffer[id] = obj_index;
    normal_buffer[id] = pack_color(&normal_color);
    depth_buffer[id] = pack_color(&depth_color);
	// if (options.sepia)
	// {
		sepia_color = color;
		color.r = (sepia_color.r * .393) + (sepia_color.g *.769) + (sepia_color.b * .189);
		color.g = (sepia_color.r * .349) + (sepia_color.g *.686) + (sepia_color.b * .168);
		color.b = (sepia_color.r * .272) + (sepia_color.g *.534) + (sepia_color.b * .131);
	// }
    color_buffer[id] = pack_color(&color);
}

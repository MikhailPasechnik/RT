#include "rt.hcl"


__kernel void k_render(
	__global t_obj* objects,
	__global t_light* lights,
	__global t_int* output,
	t_options options,
	t_cam camera
)
{
	t_ray camera_ray;
	t_hit camera_hit;
	t_color color;
	int id = get_global_id(0);
	camera_ray = new_camera_ray(&options, &camera,
			(uint2){id % options.width, id / options.height});

	if (get_global_id(0) == 0)
	{
		print_render_args(&options, &camera, objects, lights);
	}
    if (intersect(objects, options.obj_count, &camera_ray, &camera_hit) != -1)
		color = camera_hit.obj->mat.diffuse * dot(camera_ray.dir, camera_hit.norm * -1);
    else
		color = options.background_color;
	output[id] = pack_color(&color);
}

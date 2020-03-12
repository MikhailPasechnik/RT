#include "rt.hcl"

__kernel void k_render(
	t_options options,
	t_cam camera,
	__global t_obj* objects,
	__global t_light* lights,
	__global t_int* color_buffer
//	__global t_int* index_buffer
)
{
	t_ray camera_ray;
	t_int obj_index;
	t_hit camera_hit;
	t_color color;

	int id = get_global_id(0);
	camera_ray = new_camera_ray(&options, &camera,
			(uint2){id % options.width, id / options.height});

	if (get_global_id(0) == 0)
	{
		print_render_args(&options, &camera, objects, lights);
	}
	obj_index = intersect(objects, options.obj_count, &camera_ray, &camera_hit);

	if (obj_index != -1)
		color = camera_hit.obj->mat.diffuse * dot(camera_ray.dir, camera_hit.norm * -1);
    else
		color = options.background_color;

//    index_buffer[id] = obj_index;
	color_buffer[id] = pack_color(&color);
}

#include "rt.hcl"

__kernel void k_select(
		t_options options,
		t_cam camera,
		__global t_obj* objects,
		__global t_light* lights,
		__global bool* selected_objects,
		__global bool* selected_lights
)
{
	int index;
	uint2 pixel;
	t_ray camera_ray;
	t_hit camera_hit;

	pixel.x = get_global_id(0);
	pixel.y = get_global_id(1);
	camera_ray = new_camera_ray(&camera, pixel);
	index = intersect(objects, options.obj_count, &r, &camera_hit);
	selected_objects[index] |= (index != -1);
}

#include "rt.hcl"

__kernel void k_render(
    t_options options,
	t_cam camera,
	__global t_obj* objects,
	__global t_light* lights,
	__global t_int* output
)
{
//    if (get_global_id(0) == 0)
//    {
//        print_render_args(&options, &camera, scene, lights);
//    }
    int id;
	uint2 pixel;
	t_ray camera_ray;
	t_hit camera_hit;
	t_color color;

	id = get_global_id(0)
    pixel.x = id % options.width;
    pixel.y = id / options.height;
	camera_ray = new_camera_ray(&camera, pixel);
    if (intersect(objects, options.obj_count, &r, &camera_hit) != -1)
		color = camera_hit.obj->mat.diffuse * dot(r.dir, camera_hit.norm * -1);
    else
		color = options.background_color;
	output[id] = pack_color(&color);
}

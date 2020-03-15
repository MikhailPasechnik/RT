#include "rt.hcl"

__kernel void k_render(
	t_options options,
	t_cam camera,
	__global t_obj* objects,
	__global t_light* lights,
	__global t_int* color_buffer,
	__global t_int* index_buffer
)
{
	t_ray camera_ray;
	t_int obj_index;
	t_hit camera_hit;
	t_ray shadow_ray;
	t_hit shadow_hit;
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
	{
//		color = (VEC(180, 180, 180) / 255.0f) * dot(camera_ray.dir, camera_hit.norm * -1);
		color = camera_hit.obj->mat.diffuse * dot(camera_ray.dir, camera_hit.norm * -1);
		//		color = camera_hit.obj->mat.diffuse;
		// color = ((camera_hit.norm * -1) + 1) / 2;
		t_uint i = 0;
		while (i < options.light_count)
		{
			if (lights[i].id == ID_DIRECT)
			{
				shadow_ray.orig = camera_hit.pos + camera_hit.norm * 0.0001f;
				shadow_ray.dir = -dir_from_rot(lights[i].dir);
				// TODO: add bias (Shadow-Acne: Avoiding Self-Intersection)
				//  https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/ligth-and-shadows
				t_int in_shadow = intersect(objects, options.obj_count, &shadow_ray, &shadow_hit) != -1;
				if (!in_shadow)
				{
					// TODO Lambert Phong
					// color *= lights[i].intensity * dot(shadow_ray.dir, camera_hit.norm);
				}
				else
				{
					color *= 0.2f;
				}
			}
			i++;
		}
		//color = ((camera_hit.norm * -1) + 1) / 2;
	}
    else
		color = options.background_color;

    index_buffer[id] = obj_index;
	color_buffer[id] = pack_color(&color);
}

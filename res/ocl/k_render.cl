#include "rt.hcl"

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
	t_ray camera_ray;
	t_int obj_index;
	t_hit camera_hit;
	t_ray shadow_ray;
	t_hit shadow_hit;
	t_color color;
	t_color normal_color;
	t_color depth_color;

	normal_color = COLOR(0,0,0,1);
	depth_color = COLOR(0,0,0,1);
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
		depth_color = distance(camera_hit.p, VEC(camera.mtx.sC,
											 camera.mtx.sD,
											 camera.mtx.sE)) / 50.0f;

//		color = (VEC(180, 180, 180) / 255.0f) * dot(camera_ray.dir, camera_hit.n * -1);
//		color = camera_hit.obj->mat.diffuse; // * dot(camera_ray.dir, camera_hit.n * -1);
		//		color = camera_hit.obj->mat.diffuse;
		normal_color = ((camera_hit.n * -1) + 1) / 2;
		t_uint i = 0;
		color = VEC(0,0,0);
		t_vec3 diffuse = VEC(0,0,0);
		t_real specular = 0;
		while (i < options.light_count)
		{
			if (lights[i].id == ID_DIRECT)
			{
				shadow_ray.o = camera_hit.p + camera_hit.n * 0.0001f;
				shadow_ray.d = -dir_from_rot(lights[i].rot);

				// TODO: add bias (Shadow-Acne: Avoiding Self-Intersection)
				//  https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/ligth-and-shadows
				t_int in_shadow = intersect(objects, options.obj_count, &shadow_ray, &shadow_hit) != -1;

				if (!in_shadow)
				{
					// TODO Lambert Phong

					t_vec3 ref = reflect(dir_from_rot(lights[i].rot), camera_hit.n);
					specular += lights[i].intensity * pow(max(0.f, dot(ref, -camera_ray.d)), 50);
					diffuse += camera_hit.obj->mat.diffuse * lights[i].intensity * lights[i].color * max(0.f, dot(camera_hit.n, shadow_ray.d));
				}
				else
				{
//					color += 1.0f;
				}
			}
			else if (lights[i].id == ID_AMB)
			{
				// color += camera_hit.obj->mat.diffuse * lights[i].intensity * lights[i].color;
			}
			i++;
		}
		t_real kd = 1.5;
		t_real ks = 0.1;
		color = diffuse * kd + specular * ks;
		//color = ((camera_hit.n * -1) + 1) / 2;
	}
    else
		color = options.background_color;

    index_buffer[id] = obj_index;
	normal_buffer[id] = pack_color(&normal_color);
	depth_buffer[id] = pack_color(&depth_color);
	color_buffer[id] = pack_color(&color);
}

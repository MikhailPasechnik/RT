#include "rt.hcl"

static void		trace(
						int id,
						uint count,
						t_options options,
						__global t_obj* objects,
						__global t_light* lights,
						t_ray camera_ray,
						t_cam camera,
						__global t_int* color_buffer,
						__global t_int* index_buffer,
						__global t_int* normal_buffer,
						__global t_int* depth_buffer);

/*
** *********************************** **
** *********************************** **
**             random floats    	   **
** *********************************** **
** *********************************** **
*/

static float random_number(t_options options, uint count)
{
	uint2 random;

	int global_id = get_global_id(1) * get_global_size(0) + get_global_id(0);
	random.x = count % options.width;
	random.y = count / options.height;
	int seed = random.x + global_id;
	int t = seed ^ (seed << 11);  
	int result = random.y ^ (random.y >> 19) ^ (t ^ (t >> 8));
	return ((float)result / 10000.0 - result / 10000.0);
}

/** *********************************** **/

static void		trace_random_ray(
						int id,
						uint count,
						t_options options,
						__global t_obj* objects,
						__global t_light* lights,
						t_cam camera,
						t_hit camera_hit,
						__global t_int* color_buffer,
						__global t_int* index_buffer,
						__global t_int* normal_buffer,
						__global t_int* depth_buffer)
{
	float3 random_dir = (float3){random_number(options, count) - 0.5,
								 random_number(options, count) - 0.5,
								 random_number(options, count) - 0.5};
	t_ray random_ray;
	random_ray.o = camera_hit.p;
	random_ray.d = normalize(random_dir);
	if (count > 0)
	{
		trace(id, count, options, objects, lights, random_ray, camera, color_buffer, index_buffer, normal_buffer, depth_buffer);
		count--;
	}
}

static void		trace(
						int id,
						uint count,
						t_options options,
						__global t_obj* objects,
						__global t_light* lights,
						t_ray camera_ray,
						t_cam camera,
						__global t_int* color_buffer,
						__global t_int* index_buffer,
						__global t_int* normal_buffer,
						__global t_int* depth_buffer)
{
	t_int		obj_index;
	t_hit		camera_hit;
	t_ray		shadow_ray;
	t_hit		shadow_hit;
	t_color		color;
	t_color		normal_color;
	t_color		depth_color;
	t_vec3		ref;
	t_vec3		light_dir;

	normal_color = COLOR(0,0,0,1);
	depth_color = COLOR(0,0,0,1);
	obj_index = intersect(objects, options.obj_count, &camera_ray, &camera_hit);
	if (obj_index != -1)
	{
		depth_color = distance(camera_hit.p, VEC(camera.mtx.sC,
											 camera.mtx.sD,
											 camera.mtx.sE)) / 50.0f;
		normal_color = ((camera_hit.n * -1) + 1) / 2;
		t_uint i = 0;
		color = VEC(0,0,0);
		t_vec3 diffuse = VEC(0,0,0);
		t_real specular = 0;
		while (i < options.light_count)
		{
			if (lights[i].id == ID_DIRECT || lights[i].id == ID_POINT)
			{
				if (lights[i].id == ID_DIRECT)
					light_dir = dir_from_rot(lights[i].rot);
				else
					light_dir = normalize(camera_hit.p - lights[i].pos);
				shadow_ray.o = camera_hit.p + camera_hit.n * 0.001f;
				shadow_ray.d = -light_dir;
				if (!(intersect(objects, options.obj_count, &shadow_ray, &shadow_hit) != -1))
				{
					ref = reflect(light_dir, camera_hit.n);
					specular += lights[i].intensity * pow(max(0.f, dot(ref, -camera_ray.d)), 50);
					diffuse += camera_hit.obj->mat.diffuse * lights[i].intensity *
							lights[i].color * max(0.f, dot(camera_hit.n, shadow_ray.d));
				}
				else
					trace_random_ray(id, count, options, objects, lights, camera, camera_hit, color_buffer, index_buffer, normal_buffer, depth_buffer);
			}
			else if (lights[i].id == ID_AMB)
				diffuse += camera_hit.obj->mat.diffuse * lights[i].intensity * lights[i].color;
			i++;
		}
		color = diffuse * 1.5f + specular * 0.1f;
	}
    else
		color = options.background_color;

    index_buffer[id] = obj_index;
	normal_buffer[id] = pack_color(&normal_color);
	depth_buffer[id] = pack_color(&depth_color);
	color_buffer[id] = pack_color(&color);

	trace_random_ray(id, count, options, objects, lights, camera, camera_hit, color_buffer, index_buffer, normal_buffer, depth_buffer);
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
	t_ray camera_ray;
	uint count = 6;

	int id = get_global_id(0);
	camera_ray = new_camera_ray(&options, &camera,
			(uint2){id % options.width, id / options.height});
	trace(id, count, options, objects, lights, camera_ray, camera, color_buffer, index_buffer, normal_buffer, depth_buffer);
}

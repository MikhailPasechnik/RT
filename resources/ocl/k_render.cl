#include "rt.hcl"

/*
** *********************************** **
**             random floats    	   **
** *********************************** **
*/

float3	fl3_make(float3 v)
{
	return ((float3){fabs(v.x), fabs(v.y), fabs(v.z)});
}

/** *********************************** **/
/** *********************************** **/

t_int	trace(	int id,
				t_options options,
				__global t_obj* objects,
				__global t_light* lights,
				t_ray *camera_ray,
				t_cam camera,
				t_hit *camera_hit,
				t_color *color)
{
	t_int		obj_index;
	t_ray		shadow_ray;
	t_hit		shadow_hit;
	t_vec3		ref;
	t_vec3		light_dir;

	// c->normal_color = COLOR(0,0,0,1);
	// c->depth_color = COLOR(0,0,0,1);

	obj_index = intersect(objects, options.obj_count, camera_ray, camera_hit);
	*color = camera_hit->obj->mat.diffuse;
	// if (obj_index != -1)
	// {
		
	// 	// c->depth_color = distance(camera_hit->p, VEC(camera.mtx.sC,
	// 	// 									 camera.mtx.sD,
	// 	// 									 camera.mtx.sE)) / 50.0f;
	// 	// c->normal_color = ((camera_hit->n * -1) + 1) / 2;
	// 	*color = VEC(0,0,0);
	// 	t_vec3 diffuse = VEC(0,0,0);
	// 	t_real specular = 0;
	// 	t_uint i = 0;
	// 	while (i < options.light_count)
	// 	{
	// 		if (lights[i].id == ID_DIRECT || lights[i].id == ID_POINT)
	// 		{
	// 			if (lights[i].id == ID_DIRECT)
	// 				light_dir = dir_from_rot(lights[i].rot);
	// 			else
	// 				light_dir = normalize(camera_hit->p - lights[i].pos);
	// 			shadow_ray.o = camera_hit->p + camera_hit->n * 0.001f;
	// 			shadow_ray.d = -light_dir;
	// 			if (!(intersect(objects, options.obj_count, &shadow_ray, &shadow_hit) != -1))
	// 			{
	// 				ref = reflect(light_dir, camera_hit->n);
	// 				specular += lights[i].intensity * pow(max(0.f, dot(ref, -camera_ray.d)), 50);
	// 				diffuse += camera_hit->obj->mat.diffuse * lights[i].intensity *
	// 						lights[i].color * max(0.f, dot(camera_hit->n, shadow_ray.d));
	// 			}
	// 		}
	// 		else if (lights[i].id == ID_AMB)
	// 			diffuse += camera_hit->obj->mat.diffuse * lights[i].intensity * lights[i].color;
	// 		i++;
	// 	}
	// 	*color = diffuse * 1.5f + specular * 0.1f;
	// }
    // else
	// 	*color = options.background_color;
	// printf("obj_index = %d\n", obj_index);
	return (obj_index);
}

void	fill_buffers(int id,
					t_int obj_index,
					t_color normal_color,
					t_color depth_color,
					t_color color,
					__global t_int* color_buffer,
					__global t_int* index_buffer,
					__global t_int* normal_buffer,
					__global t_int* depth_buffer)
{
    index_buffer[id] = obj_index;
	normal_buffer[id] = pack_color(&normal_color);
	depth_buffer[id] = pack_color(&depth_color);
	color_buffer[id] = pack_color(&color);
}

t_color pathtracing(int id,
					t_options options,
					__global t_obj* objects,
					__global t_light* lights,
					t_ray *camera_ray,
					t_cam camera,
					int *obj_index)
{
	t_hit	camera_hit;
	t_color color;
	float3	accumulate_color;
	float3	mask;
	float	bounce;
	float	max_bounce;
	int		true_obj_index;

	bounce = 0;
	max_bounce = 500;
	accumulate_color = fl3_make((float3){0.0f, 0.0f, 0.0f});
	mask = fl3_make((float3){1.0f, 1.0f, 1.0f});
	obj_index = 0;
	while (bounce < max_bounce)
	{
		obj_index = trace(id, options, objects, lights, camera_ray, camera, &camera_hit, &color);
		printf("%d\n", obj_index);
		if (obj_index == -1)
			return (fl3_make((float3){0.0f, 0.0f, 0.0f}));
		if (bounce == 0)
			true_obj_index = obj_index;
		accumulate_color += mask * camera_hit.obj->mat.emittance;
		camera_ray->o = camera_hit.p * 0.05f;
		camera_ray->d = random_dir(bounce, options, camera_hit.n);
		// printf("%f %f %f\n", camera_hit.n);
		mask *= color;
		mask *= v3_dot_product(camera_ray->d, camera_hit.n);
		mask *= 2.0f;
	}
	obj_index = true_obj_index;
	return (accumulate_color);
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
	t_ray		camera_ray;
	float3		orig_pix;
	t_int		*obj_index;
	t_color		radiance;
	uint		sample;
	uint		max_samples;
	t_hit camera_hit;
	t_color color;

	sample = 0;
	max_samples = 500;
	radiance = fl3_make(0.0f);
	int id = get_global_id(0);
	camera_ray = new_camera_ray(&options, &camera,
			(uint2){id % options.width, id / options.height});
	orig_pix = camera_ray.o;
	while (sample < max_samples)
	{
		camera_ray.o = orig_pix;
		radiance = radiance + v3_mult_vec_const(pathtracing(id, options, objects, lights, &camera_ray, camera, obj_index), (1. / max_samples));
		sample++;
	}
	fill_buffers(id, *obj_index, radiance, radiance, radiance, color_buffer, index_buffer, normal_buffer, depth_buffer);
	// obj_index = trace(id, options, objects, lights, &camera_ray, camera, &camera_hit, &color);
	// fill_buffers(id, *obj_index, color, color, color, color_buffer, index_buffer, normal_buffer, depth_buffer);
}

#include "rt.hcl"

/*
** *********************************** **
**             random floats    	   **
** *********************************** **
*/


/** *********************************** **/
/** *********************************** **/

t_int	trace(	int id,
				t_options options,
				__global t_obj* objects,
				__global t_light* lights,
				t_ray camera_ray,
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
	obj_index = intersect(objects, options.obj_count, &camera_ray, camera_hit);
	if (obj_index != -1)
	{
		// c->depth_color = distance(camera_hit->p, VEC(camera.mtx.sC,
		// 									 camera.mtx.sD,
		// 									 camera.mtx.sE)) / 50.0f;
		// c->normal_color = ((camera_hit->n * -1) + 1) / 2;
		*color = VEC(0,0,0);
		t_vec3 diffuse = VEC(0,0,0);
		t_real specular = 0;
		t_uint i = 0;
		while (i < options.light_count)
		{
			if (lights[i].id == ID_DIRECT || lights[i].id == ID_POINT)
			{
				if (lights[i].id == ID_DIRECT)
					light_dir = dir_from_rot(lights[i].rot);
				else
					light_dir = normalize(camera_hit->p - lights[i].pos);
				shadow_ray.o = camera_hit->p + camera_hit->n * 0.001f;
				shadow_ray.d = -light_dir;
				if (!(intersect(objects, options.obj_count, &shadow_ray, &shadow_hit) != -1))
				{
					ref = reflect(light_dir, camera_hit->n);
					specular += lights[i].intensity * pow(max(0.f, dot(ref, -camera_ray.d)), 50);
					diffuse += camera_hit->obj->mat.diffuse * lights[i].intensity *
							lights[i].color * max(0.f, dot(camera_hit->n, shadow_ray.d));
				}
			}
			else if (lights[i].id == ID_AMB)
				diffuse += camera_hit->obj->mat.diffuse * lights[i].intensity * lights[i].color;
			i++;
		}
		*color = diffuse * 1.5f + specular * 0.1f;
	}
    else
		*color = options.background_color;
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

t_color trace_one_path(int id,
					t_options options,
					__global t_obj* objects,
					__global t_light* lights,
					t_ray *camera_ray,
					t_cam camera,
					t_hit *camera_hit,
					t_color *color,
					int depth,
					int *obj_index,
					t_pathtrace *b)
{
	t_mat	material;

	*obj_index = trace(id, options, objects, lights, *camera_ray, camera, camera_hit, color);
	if (*obj_index == -1)
		return (BLACK);
	material = camera_hit->obj->mat;
	b->emittance = material.specular;
	camera_ray->o = camera_hit->p;
	camera_ray->d = random_dir(depth, options, camera_hit->n);
	b->cos_theta = v3_dot_product(camera_ray->d, camera_hit->n);
	b->BRDF = material.reflection / M_PI;
	return (*color);
}

	// return (emittance + (BRDF * incoming * cos_theta / probability));

t_color pathtracing(int id,
					t_options options,
					__global t_obj* objects,
					__global t_light* lights,
					t_ray camera_ray,
					t_cam camera,
					t_hit *camera_hit,
					t_color *c,
					int *obj_index)
{
	int			iter;
	int			max_iter;
	int			*true_obj_index;
	t_pathtrace bounce[DEPTH];
	t_color		col;

	iter = 0;
	max_iter = 6;
	while (iter < max_iter && !compare_color(col, BLACK))
	{
		col = trace_one_path(id, options, objects, lights, &camera_ray, camera, camera_hit, c, iter, obj_index, &bounce[iter]);
		if (iter == 0)
			true_obj_index = obj_index;
		iter++;
	}
	if (iter == 0)
		bounce[iter].incoming = BLACK;
	if (!compare_color(col, BLACK))
	{
		iter--;
		bounce[iter].incoming = BLACK;
	}
	while (iter > 0)
	{
		bounce[iter - 1].incoming = bounce[iter].emittance + (v3_division_vec_on_const((v3_mult_vec_const(bounce[iter].BRDF * bounce[iter].incoming, (float)bounce[iter].cos_theta)), PROBABILITY));
		iter--;
	}
	obj_index = true_obj_index;
	return (bounce[0].incoming);
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
	t_hit		camera_hit;
	float3		orig_pix;
	t_int		*obj_index;
	t_color		color;
	t_color		add_light;
	uint		max_bounces = 10;
	uint		bounce = 0;

	bounce = 0;
	int id = get_global_id(0);
	camera_ray = new_camera_ray(&options, &camera,
			(uint2){id % options.width, id / options.height});
	orig_pix = camera_hit.p;
	while (bounce < max_bounces)
	{
		camera_ray.o = orig_pix;
		add_light += pathtracing(id, options, objects, lights, camera_ray, camera, &camera_hit, &color, obj_index);
		bounce++;
	}
	add_light.x = add_light.x / max_bounces;
	add_light.y = add_light.y / max_bounces;
	add_light.z = add_light.z / max_bounces;
	// add_light /= max_bounces;
	// obj_index = trace(id, options, objects, lights, camera_ray, camera, &camera_hit, &color);
	fill_buffers(id, *obj_index, add_light, add_light, add_light, color_buffer, index_buffer, normal_buffer, depth_buffer);
}

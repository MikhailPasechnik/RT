#include "rt.hcl"

/*
** *********************************** **
**             random floats    	   **
** *********************************** **
*/

float random_number(t_options options, uint count)
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

float3		random_dir(uint bounce, t_options options)
{
	float3 random_dir = (float3){random_number(options, bounce) - 0.5,
								 random_number(options, bounce + 1) - 0.5,
								 random_number(options, bounce + 2) - 0.5};
	random_dir = normalize(random_dir);
	// √−2 ln 𝑥1 cos (2𝜋𝑥2);
	return (random_dir);
}

t_int	trace(	int id,
				t_options options,
				__global t_obj* objects,
				__global t_light* lights,
				t_ray camera_ray,
				t_cam camera,
				t_hit *camera_hit,
				t_colors *c)
{
	t_int		obj_index;
	t_ray		shadow_ray;
	t_hit		shadow_hit;
	t_vec3		ref;
	t_vec3		light_dir;

	c->normal_color = COLOR(0,0,0,1);
	c->depth_color = COLOR(0,0,0,1);
	obj_index = intersect(objects, options.obj_count, &camera_ray, camera_hit);
	if (obj_index != -1)
	{
		c->depth_color = distance(camera_hit->p, VEC(camera.mtx.sC,
											 camera.mtx.sD,
											 camera.mtx.sE)) / 50.0f;
		c->normal_color = ((camera_hit->n * -1) + 1) / 2;
		c->color = VEC(0,0,0);
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
		c->color = diffuse * 1.5f + specular * 0.1f;
	}
    else
		c->color = options.background_color;
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
	t_int		obj_index;
	t_colors	c;
	t_colors	major_light;
	t_colors	add_light;
	uint		max_bounces = 10;
	uint		count_random_rays = 100;
	uint		bounce = 0;
	uint		i = 0;

	int id = get_global_id(0);
	camera_ray = new_camera_ray(&options, &camera,
			(uint2){id % options.width, id / options.height});
	obj_index = trace(id, options, objects, lights, camera_ray, camera, &camera_hit, &c);
	orig_pix = camera_hit.p;
	camera_ray.o = orig_pix;
	major_light.normal_color = c.normal_color;
	major_light.depth_color = c.depth_color;
	major_light.color = c.color;
	while (i < count_random_rays)
	{
		camera_ray.o = orig_pix;
		camera_ray.d = random_dir(bounce, options);
		obj_index = trace(id, options, objects, lights, camera_ray, camera, &camera_hit, &c);
		add_light.normal_color += c.normal_color;
		add_light.depth_color += c.depth_color;
		add_light.color += c.color;
		bounce = 0;
		while (bounce < max_bounces) //  ||			???(если bounce не первый и отскочил в свет)
		{
			camera_ray.o = camera_hit.p;
			camera_ray.d = random_dir(bounce, options);
			obj_index = trace(id, options, objects, lights, camera_ray, camera, &camera_hit, &c);
			add_light.normal_color += c.normal_color;
			add_light.depth_color += c.depth_color;
			add_light.color += c.color;
			bounce++;
		}
		add_light.normal_color.x = add_light.normal_color.x / max_bounces;
		add_light.normal_color.y = add_light.normal_color.y / max_bounces;
		add_light.normal_color.z = add_light.normal_color.z / max_bounces;

		add_light.depth_color.x = add_light.depth_color.x / max_bounces;
		add_light.depth_color.y = add_light.depth_color.y / max_bounces;
		add_light.depth_color.z = add_light.depth_color.z / max_bounces;

		add_light.color.x = add_light.color.x / max_bounces;
		add_light.color.y = add_light.color.y / max_bounces;
		add_light.color.z = add_light.color.z / max_bounces;		
		i++;
	}
	add_light.normal_color.x = add_light.normal_color.x / count_random_rays;
	add_light.normal_color.y = add_light.normal_color.y / count_random_rays;
	add_light.normal_color.z = add_light.normal_color.z / count_random_rays;

	add_light.depth_color.x = add_light.depth_color.x / count_random_rays;
	add_light.depth_color.y = add_light.depth_color.y / count_random_rays;
	add_light.depth_color.z = add_light.depth_color.z / count_random_rays;

	add_light.color.x = add_light.color.x / count_random_rays;
	add_light.color.y = add_light.color.y / count_random_rays;
	add_light.color.z = add_light.color.z / count_random_rays;


	c.normal_color = major_light.normal_color + add_light.normal_color;
	c.depth_color = major_light.depth_color + add_light.depth_color;
	c.color = major_light.color + add_light.color;

	fill_buffers(id, obj_index, c.normal_color, c.depth_color, c.color, color_buffer, index_buffer, normal_buffer, depth_buffer);
}

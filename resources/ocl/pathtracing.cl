#include "rt.hcl"

float	random_number(t_options options, uint count)
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
/** *********************************** **/

t_mat3		create_rot_matrix(float3 normal)
{
	float3	transit_vec;
	float3	x_axis;
	float3	z_axis;
	t_mat3	rot_matrix;

	transit_vec = (float3){normal.x, normal.y * (-1), normal.z};
	transit_vec = normalize(transit_vec);
	x_axis = v3_cross(normal, transit_vec);
	x_axis = normalize(x_axis);
	z_axis = v3_cross(x_axis, normal);
	z_axis = normalize(z_axis);

	rot_matrix.a.x = x_axis.x;
	rot_matrix.a.y = x_axis.y;
	rot_matrix.a.z = x_axis.z;

	rot_matrix.b.x = normal.x;
	rot_matrix.b.y = normal.y;
	rot_matrix.b.z = normal.z;

	rot_matrix.c.x = z_axis.x;
	rot_matrix.c.y = z_axis.y;
	rot_matrix.c.z = z_axis.z;

	// rot_matrix.a = x_axis;
	// rot_matrix.b = normal;
	// rot_matrix.c = z_axis;
	return (rot_matrix);
}

float3		rotation_random_dir(float3 normal, float3 random_dir)
{
	t_mat3 rotation_matrix;
	float3 rot_random_dir;

	rotation_matrix = create_rot_matrix(normal);
	// printf("%f %f %f\n", rotation_matrix.a.x, rotation_matrix.a.y, rotation_matrix.a.z);
	rot_random_dir = v3_mult_matrix(rotation_matrix, random_dir);
	rot_random_dir = normalize(rot_random_dir);
	return (random_dir);
}

float3		random_dir(uint bounce, t_options options, float3 normal)
{
	float3 random_dir;
	float3 rot_random_dir;
	
	random_dir = (float3){random_number(options, bounce) - 0.5,
								 fabs(random_number(options, bounce + 1) - 0.5),
								 random_number(options, bounce + 2) - 0.5};
	random_dir = normalize(random_dir);
	rot_random_dir = rotation_random_dir(normal, random_dir);
	return (rot_random_dir);
}





t_color trace_path(int id,
					t_options options,
					__global t_obj* objects,
					__global t_light* lights,
					t_ray camera_ray,
					t_cam camera,
					t_hit *camera_hit,
					t_colors *c)
{
	t_ray	new_ray;
	t_mat	material;
	t_color	emittance;
	float	probability;
	float	cos_theta;
	t_color	BRDF;
	t_color	incoming;
	int		depth;
	int		max_depth;

	depth = 0;
	max_depth = 6;
	obj_index = trace(id, options, objects, lights, camera_ray, camera, &camera_hit, &c);
	if (obj_index == -1)
		return (*c);
	material = camera_hit->obj->mat;
	emittance = material.emittance;
	new_ray.o = camera_hit.p;
	new_ray.d = random_dir(bounce, options, camera_hit.n);
	probability = 1 / (2 * M_PI);
	cos_theta = dot_product(new_ray.d, camera_hit.n);
	BRDF = material.reflection / M_PI;
	while (depth < max_depth)
		incoming += trace_path(new_ray, depth + 1);
	return (emmitance + (BRDF * incoming * cos_theta / probability));
}














// __kernel void k_render(
// 	t_options options,
// 	t_cam camera,
// 	__global t_obj* objects,
// 	__global t_light* lights,
// 	__global t_int* color_buffer,
// 	__global t_int* index_buffer,
// 	__global t_int* normal_buffer,
// 	__global t_int* depth_buffer
// )
// {
// 	t_ray		camera_ray;
// 	t_hit		camera_hit;
// 	float3		orig_pix;
// 	t_int		obj_index;
// 	t_colors	c;
// 	t_colors	major_light;
// 	t_colors	add_light;
// 	uint		max_bounces = 15;
// 	uint		count_random_rays = 70;
// 	uint		bounce = 0;
// 	uint		i = 0;

// 	int id = get_global_id(0);
// 	camera_ray = new_camera_ray(&options, &camera,
// 			(uint2){id % options.width, id / options.height});
// 	obj_index = trace(id, options, objects, lights, camera_ray, camera, &camera_hit, &c);
// 	orig_pix = camera_hit.p;
// 	camera_ray.o = orig_pix;
// 	major_light.normal_color = c.normal_color;
// 	major_light.depth_color = c.depth_color;
// 	major_light.color = c.color;
// 	while (i < count_random_rays)
// 	{
// 		camera_ray.o = orig_pix;
// 		camera_ray.d = random_dir(bounce, options, camera_hit.n);
// 		obj_index = trace(id, options, objects, lights, camera_ray, camera, &camera_hit, &c);
// 		add_light.normal_color += c.normal_color;
// 		add_light.depth_color += c.depth_color;
// 		add_light.color += c.color;
// 		bounce = 0;
// 		while (bounce < max_bounces) //  ||			???(если bounce не первый и отскочил в свет)
// 		{
// 			camera_ray.o = camera_hit.p;
// 			camera_ray.d = random_dir(bounce, options, camera_hit.n);
// 			obj_index = trace(id, options, objects, lights, camera_ray, camera, &camera_hit, &c);
// 			add_light.normal_color += c.normal_color;
// 			add_light.depth_color += c.depth_color;
// 			add_light.color += c.color;
// 			bounce++;
// 		}
// 		add_light.normal_color.x = add_light.normal_color.x / max_bounces;
// 		add_light.normal_color.y = add_light.normal_color.y / max_bounces;
// 		add_light.normal_color.z = add_light.normal_color.z / max_bounces;

// 		add_light.depth_color.x = add_light.depth_color.x / max_bounces;
// 		add_light.depth_color.y = add_light.depth_color.y / max_bounces;
// 		add_light.depth_color.z = add_light.depth_color.z / max_bounces;

// 		add_light.color.x = add_light.color.x / max_bounces;
// 		add_light.color.y = add_light.color.y / max_bounces;
// 		add_light.color.z = add_light.color.z / max_bounces;		
// 		i++;
// 	}

// 	add_light.normal_color.x = (add_light.normal_color.x / count_random_rays) * 2 * M_PI;
// 	add_light.normal_color.y = (add_light.normal_color.y / count_random_rays) * 2 * M_PI;
// 	add_light.normal_color.z = (add_light.normal_color.z / count_random_rays) * 2 * M_PI;

// 	add_light.depth_color.x = (add_light.depth_color.x / count_random_rays) * 2 * M_PI;
// 	add_light.depth_color.y = (add_light.depth_color.y / count_random_rays) * 2 * M_PI;
// 	add_light.depth_color.z = (add_light.depth_color.z / count_random_rays) * 2 * M_PI;

// 	add_light.color.x = (add_light.color.x / count_random_rays) * 2 * M_PI;
// 	add_light.color.y = (add_light.color.y / count_random_rays) * 2 * M_PI;
// 	add_light.color.z = (add_light.color.z / count_random_rays) * 2 * M_PI;


// 	c.normal_color = major_light.normal_color + add_light.normal_color;
// 	c.depth_color = major_light.depth_color + add_light.depth_color;
// 	c.color = major_light.color + add_light.color;

// 	fill_buffers(id, obj_index, c.normal_color, c.depth_color, c.color, color_buffer, index_buffer, normal_buffer, depth_buffer);
// }

// __kernel void k_render(
// 	t_options options,
// 	t_cam camera,
// 	__global t_obj* objects,
// 	__global t_light* lights,
// 	__global t_int* color_buffer,
// 	__global t_int* index_buffer,
// 	__global t_int* normal_buffer,
// 	__global t_int* depth_buffer
// )
// {
// 	t_ray		camera_ray;
// 	t_hit		camera_hit;
// 	float3		orig_pix;
// 	t_int		obj_index;
// 	t_colors	c;
// 	t_colors	major_light;
// 	t_colors	add_light;
// 	uint		max_bounces = 100;
// 	uint		bounce = 0;

// 	int id = get_global_id(0);
// 	camera_ray = new_camera_ray(&options, &camera,
// 			(uint2){id % options.width, id / options.height});
// 	obj_index = trace(id, options, objects, lights, camera_ray, camera, &camera_hit, &c);
// 	orig_pix = camera_hit.p;
// 	camera_ray.o = orig_pix;
// 	// major_light.normal_color = c.normal_color;
// 	// major_light.depth_color = c.depth_color;
// 	// major_light.color = c.color;

// 	add_light.normal_color += c.normal_color;
// 	add_light.depth_color += c.depth_color;
// 	add_light.color += c.color;
// 	bounce = 0;
// 	while (bounce < max_bounces)
// 	{
// 		camera_ray.o = camera_hit.p;
// 		camera_ray.d = random_dir(bounce, options, camera_hit.n);
// 		obj_index = trace(id, options, objects, lights, camera_ray, camera, &camera_hit, &c);
// 		add_light.normal_color += c.normal_color;
// 		add_light.depth_color += c.depth_color;
// 		add_light.color += c.color;
// 		bounce++;
// 	}

// 	// add_light.normal_color.x = add_light.normal_color.x / max_bounces;
// 	// add_light.normal_color.y = add_light.normal_color.y / max_bounces;
// 	// add_light.normal_color.z = add_light.normal_color.z / max_bounces;

// 	add_light.normal_color.x = ((2 * M_PI) / max_bounces) * add_light.normal_color.x;
// 	add_light.normal_color.y = ((2 * M_PI) / max_bounces) * add_light.normal_color.y;
// 	add_light.normal_color.z = ((2 * M_PI) / max_bounces) * add_light.normal_color.z;


// 	// add_light.depth_color.x = add_light.depth_color.x / max_bounces;
// 	// add_light.depth_color.y = add_light.depth_color.y / max_bounces;
// 	// add_light.depth_color.z = add_light.depth_color.z / max_bounces;

// 	add_light.depth_color.x = ((2 * M_PI) / max_bounces) * add_light.depth_color.x;
// 	add_light.depth_color.y = ((2 * M_PI) / max_bounces) * add_light.depth_color.y;
// 	add_light.depth_color.z = ((2 * M_PI) / max_bounces) * add_light.depth_color.z;


// 	// add_light.color.x = add_light.color.x / max_bounces;
// 	// add_light.color.y = add_light.color.y / max_bounces;
// 	// add_light.color.z = add_light.color.z / max_bounces;

// 	add_light.color.x = ((2 * M_PI) / max_bounces) * add_light.color.x;
// 	add_light.color.y = ((2 * M_PI) / max_bounces) * add_light.color.y;
// 	add_light.color.z = ((2 * M_PI) / max_bounces) * add_light.color.z;


// 	// c.normal_color = major_light.normal_color + add_light.normal_color;
// 	// c.depth_color = major_light.depth_color + add_light.depth_color;
// 	// c.color = major_light.color + add_light.color;

// 	c.normal_color = add_light.normal_color;
// 	c.depth_color = add_light.depth_color;
// 	c.color = add_light.color;

// 	fill_buffers(id, obj_index, c.normal_color, c.depth_color, c.color, color_buffer, index_buffer, normal_buffer, depth_buffer);
// }


	// return (emittance + (BRDF * incoming * cos_theta / probability));
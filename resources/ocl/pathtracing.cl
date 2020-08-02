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




// t_color trace_one_path(int id,
// 					t_options options,
// 					__global t_obj* objects,
// 					__global t_light* lights,
// 					t_ray *camera_ray,
// 					t_cam camera,
// 					t_hit *camera_hit,
// 					t_color *color,
// 					int depth,
// 					int *obj_index,
// 					t_pathtrace *b)
// {
// 	t_mat	material;

// 	*obj_index = trace(id, options, objects, lights, *camera_ray, camera, camera_hit, color);
// 	if (*obj_index == -1)
// 		return (BLACK);
// 	material = camera_hit->obj->mat;
// 	b->emittance = material.emittance;
// 	camera_ray->o = camera_hit->p;
// 	camera_ray->d = random_dir(depth, options, camera_hit->n);
// 	b->cos_theta = v3_dot_product(camera_ray->d, camera_hit->n);
// 	b->BRDF = material.reflection / M_PI;
// 	return (*color);
// }

// 	// return (emittance + (BRDF * incoming * cos_theta / probability));

// t_color pathtracing(int id,
// 					t_options options,
// 					__global t_obj* objects,
// 					__global t_light* lights,
// 					t_ray camera_ray,
// 					t_cam camera,
// 					t_hit *camera_hit,
// 					t_color *c,
// 					int *obj_index)
// {
// 	int			iter;
// 	int			max_iter;
// 	int			*true_obj_index;
// 	t_pathtrace bounce[DEPTH];
// 	t_color		col;

// 	iter = 0;
// 	max_iter = 6;
// 	while (iter < max_iter && !compare_color(col, BLACK))
// 	{
// 		col = trace_one_path(id, options, objects, lights, &camera_ray, camera, camera_hit, c, iter, obj_index, &bounce[iter]);
// 		if (iter == 0)
// 			true_obj_index = obj_index;
// 		iter++;
// 	}
// 	if (iter == 0)
// 		bounce[iter].incoming = BLACK;
// 	if (!compare_color(col, BLACK))
// 	{
// 		iter--;
// 		bounce[iter].incoming = BLACK;
// 	}
// 	while (iter > 0)
// 	{
// 		bounce[iter - 1].incoming = bounce[iter].emittance + (v3_division_vec_on_const((v3_mult_vec_const(bounce[iter].BRDF * bounce[iter].incoming, (float)bounce[iter].cos_theta)), PROBABILITY));
// 		iter--;
// 	}
// 	obj_index = true_obj_index;
// 	return (bounce[0].incoming);
// }

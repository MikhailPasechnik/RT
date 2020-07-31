#include "rt.hcl"

/*
** *********************************** **
**             random floats    	   **
** *********************************** **
*/

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

t_color trace_path(int id,
					t_options options,
					__global t_obj* objects,
					__global t_light* lights,
					t_ray camera_ray,
					t_cam camera,
					t_hit *camera_hit,
					t_color *color,
					int depth,
					int *obj_index)
{
	t_mat	material;
	t_color	emittance;
	float	probability;
	float	cos_theta;
	t_color	BRDF;

	*obj_index = trace(id, options, objects, lights, camera_ray, camera, camera_hit, color);
	if (*obj_index == -1)
		return (*color);
	material = camera_hit->obj->mat;
	emittance = material.specular;
	camera_ray.o = camera_hit->p;
	camera_ray.d = random_dir(depth, options, camera_hit->n);
	probability = 1 / (2 * M_PI);
	cos_theta = dot_product(camera_ray.d, camera_hit->n);
	BRDF = material.reflection / M_PI;
	return (emittance + (BRDF * *color * cos_theta / probability));
}

t_color instead_of_recursion(int id,
							t_options options,
							__global t_obj* objects,
							__global t_light* lights,
							t_ray camera_ray,
							t_cam camera,
							t_hit *camera_hit,
							t_color *c,
							int *obj_index)
{
	int		depth;
	int		max_depth;
	t_color	incoming;
	int		*true_obj_index;

	depth = 0;
	max_depth = 6;
	while (depth < max_depth)
	{
		incoming += trace_path(id, options, objects, lights, camera_ray, camera, camera_hit, c, depth, obj_index);
		if (depth == 0)
			true_obj_index = obj_index;
		depth++;
	}
	obj_index = true_obj_index;
	return (incoming);
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
	t_color		c;
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
		// add_light += instead_of_recursion(id, options, objects, lights, camera_ray, camera, &camera_hit, &c, obj_index);
		bounce++;
	}
	add_light /= max_bounces;
	fill_buffers(id, *obj_index, add_light, add_light, add_light, color_buffer, index_buffer, normal_buffer, depth_buffer);
}

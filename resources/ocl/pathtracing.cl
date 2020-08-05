
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
						  (random_number(options, bounce + 2) - 0.5)};
	random_dir = normalize(random_dir);
	rot_random_dir = rotation_random_dir(normal, random_dir);
	rot_random_dir = normalize(rot_random_dir);
	return (rot_random_dir);
}

float3 sampleWorld(float3 Nt, float3 Nb, float3 hitNormal, float3 sample)
{ 
	float3 sample_upgrade;

	sample_upgrade = sample.x * Nb.x + sample.y * hitNormal.x + sample.z * Nt.x;
	sample_upgrade = sample.x * Nb.y + sample.y * hitNormal.y + sample.z * Nt.y;
	sample_upgrade = sample.x * Nb.z + sample.y * hitNormal.z + sample.z * Nt.z;
	return (sample_upgrade);
}

float3 uniformSampleHemisphere(const float r1, const float r2)
{ 
    // cos(theta) = r1 = y
    // cos^2(theta) + sin^2(theta) = 1 -> sin(theta) = srtf(1 - cos^2(theta))
    float sinTheta = sqrtf(1 - r1 * r1); 
    float phi = 2 * M_PI * r2; 
    float x = sinTheta * cosf(phi); 
    float y = phi / (2 + M_PI);
	float z = sinTheta * sinf(phi); 
    return Vec3f(x, y, z);
}

void createCoordinateSystem(const float3 N, float3 *Nt, float3 *Nb) 
{
    if (fabs(N.x) > fabs(N.y)) 
        *Nt = Vec3f(N.z, 0, -N.x) / sqrtf(N.x * N.x + N.z * N.z); 
    else 
        *Nt = Vec3f(0, -N.z, N.y) / sqrtf(N.y * N.y + N.z * N.z);
    *Nb = v3_cross(N, *Nt);
}

float3 random_dir_v20(uint bounce, t_options options, float3 normal)
{
	t_vec3 *Nt;
	t_vec3 *Nb;
	t_vec3 sample;

	createCoordinateSystem(normal, Nt, Nb);
	sample = uniformSampleHemisphere(random_number(options, bounce) - 0.5, random_number(options, bounce + 1) - 0.5);
	sample = sampleWorld(*Nt, *Nb, normal, sample);
	sample = normalize(sample);
	return (sample);
}

t_color trace_one_path(t_options options, __global t_obj* objects, __global t_light* lights, t_ray camera_ray, t_hit camera_hit)
{
	int		bounce;
	int		max_bounce;
	int		i;
	t_color main;
	t_vec3	irradiance;
	int		obj_index;
	t_vec3	light_dir;
	t_ray	shadow_ray;
	t_hit	shadow_hit;

	irradiance = 0;
	main = 0;
	bounce = 0;
	max_bounce = 15;
	while (bounce < max_bounce)
	{
		if (bounce != 0)
		{	
			camera_ray.o = camera_hit.p;
			// camera_ray.d = random_dir(bounce, options, camera_hit.n);
			camera_ray.d = random_dir_v20(bounce, options, camera_hit.n);
			// camera_ray.d = (t_vec3){random_number(options, bounce) - 0.5,
			// 			  random_number(options, bounce + 1) - 0.5,
			// 			  fabs(random_number(options, bounce + 2) - 0.5)};
			obj_index = intersect(objects, options.obj_count, &camera_ray, &camera_hit);
		}
		if (obj_index == -1)
			break ;
		i = 0;
		while (i < options.light_count)
		{
			if (lights[i].id == ID_DIRECT || lights[i].id == ID_POINT)
			{
				light_dir = (lights[i].id == ID_DIRECT) ? dir_from_rot(lights[i].rot)
					: normalize(camera_hit.p - lights[i].pos);
				shadow_ray.o = camera_hit.p + camera_hit.n * 0.001f;
				shadow_ray.d = -light_dir;
				if (!(intersect(objects, options.obj_count, &shadow_ray, &shadow_hit) != -1))
				{
					irradiance += camera_hit.obj->mat.diff * lights[i].intensity * lights[i].color * clamp(dot(camera_hit.n, shadow_ray.d), 0.0f, 1.0f);
				}
			}
			else if (lights[i].id == ID_AMB)
				irradiance += camera_hit.obj->mat.diff * lights[i].intensity * lights[i].color;
			i++;
		}
		main += irradiance;
		bounce++;
	}
	main = main / bounce;
	return (main);
}

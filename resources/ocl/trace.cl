#include "rt.hcl"

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

t_vec3	v3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3 v;

	v.x = a.y * b.z - a.z * b.y;
	v.y = a.z * b.x - a.x * b.z;
	v.z = a.x * b.y - a.y * b.x;
	return (v);
}

float2 get_sphere_uv(t_vec3 p)
{
	float2 uv;

	float phi;
	float theta;

	p = normalize(p);
	phi = atan2(p.z, p.x);
	theta = asin(p.y);
	uv.x = 1 - (phi + M_PI) / (2.0f * M_PI);
	uv.y = (theta + M_PI / 2.0f) / M_PI;
	return (uv);
}

float2 get_cube_uv(t_vec3 p)
{
	float2 uv;
	uv.x = (p.x + 1.0f) / 2.0f;
	uv.y = (p.y + 1.0f) / 2.0f;
	return (uv);
}

float2 get_cylinder_uv(t_vec3 p, float height, float radius)
{
	float2 uv;

	uv.y = p.z / height;
	uv.x = acos(p.x / radius) / (2 * M_PI);
	if (p.y < 0)
		uv.x = 1 - uv.x;
	return (uv);
}

// float2 get_cone_uv(t_vec3 p, float height, float radius, float radius_on_height)
// {
// 	float2 uv;

// 	uv.y = p.z / height;
// 	uv.x = (acos(p.x / radius + (radius_on_height - radius) * p.z / height)) / (2 * M_PI);
// 	if (p.y < 0)
// 		uv.x = 1 - uv.x;
// 	return (uv);
// }

float2 get_plane_uv(t_vec3 p, t_vec3 n)
{
	float2 uv;
	t_vec3 prepare_uv_x;
	t_vec3 prepare_uv_y;

	if (n.x != 0 && n.y != 0)
		prepare_uv_x = normalize((t_vec3){n.y, -n.x, 0.0f});
	else
		prepare_uv_x = normalize((t_vec3){n.z, n.z, 0.0f});
	prepare_uv_y = v3_cross(n, prepare_uv_x);
	uv.x = dot(prepare_uv_x, p);
	uv.y = dot(prepare_uv_y, p);
	return (uv);
}

static void swap(t_real *a, t_real *b)
{
	t_real tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static t_int solve_quadratic(t_real a, t_real b, t_real c,
		t_real *t0, t_real *t1)
{
	t_real discriminant;

	discriminant = b * b - 4.0 * a * c;
	if (discriminant < EPSILON)
		return (0);
	discriminant = sqrt(discriminant);
	float q;
	if (b < 0)
		q = -.5f * (b - discriminant);
	else
		q = -.5f * (b + discriminant);
	*t0 = q / a;
	*t1 = c / q;
	if (*t0 > *t1)
		swap(t0, t1);
	return (1);
}

static void ray_to_object_space(__global t_obj *obj, t_ray *ray)
{
	t_mat4 transpose_obj_space;

	m4_identity(&transpose_obj_space);
	m4_set_rotation(&transpose_obj_space, obj->rot);
	transpose_obj_space = m4_transpose(transpose_obj_space);
	ray->o -= obj->pos;
	ray->o = m4_mul_vec3(&transpose_obj_space, &ray->o);
	ray->d = m4_mul_vec3(&transpose_obj_space, &ray->d);
}

static void hit_to_world_space(__global t_obj *obj, t_hit *hit)
{
	t_mat4 object_space;

	m4_identity(&object_space);
	m4_set_rotation(&object_space, obj->rot);
	hit->n = m4_mul_vec3(&object_space, &hit->n);
	hit->p =  m4_mul_vec3(&object_space, &hit->p);
	hit->p += obj->pos;
}

static int disk_trace(t_vec3 dir, t_vec3 pos,
		t_real radius, t_ray *ray, t_hit *hit)
{
	t_vec3 hit_pos;
	t_real d;
    t_real t;

	d = dot(dir, ray->d);
	if (d > EPSILON)
	{
		t = dot(pos - ray->o, dir) / d;
		if (t < 0)
			return (0);
		hit_pos = ray->o + ray->d * t;
		d = dot(hit_pos - pos, hit_pos - pos);
		if (sqrt(d) > radius)
			return (0);
		hit->p = hit_pos;
		hit->n = -dir;
		return (1);
	}
	return (0);
}

static int sphere_trace(__global t_obj *obj, t_ray ray, t_hit *hit)
{
    t_real a;
    t_real b;
    t_real c;
    t_real t0;
    t_real t1;

	ray_to_object_space(obj, &ray);

	a = dot(ray.d, ray.d);
	b = 2 * dot(ray.d, ray.o);
	c = dot(ray.o, ray.o) - (obj->radius * obj->radius);

	if (!solve_quadratic(a, b, c, &t0, &t1))
		return (0);
	
	if (t0 < 0)
		return (0);
	
    hit->p = ray.o + ray.d * t0;
    hit->n = normalize(hit->p);
    hit->obj = obj;
	hit->uv = get_sphere_uv(hit->p);
	hit_to_world_space(obj, hit);
    return (1);
}

/*
** Plane intersections:
**    First test that ray is not parallel and facing ray:
**       The dot product between the ray and the plane normal will be > 0
**       if they are facing each other, and < 0 if looking away.
**
**       (p−p0) ⋅ n = 0   Point on plane
**       r0 + r ∗ t = p   Point on ray
**
**       Insert ray equation into plane equation
**
**       r ∗ t ⋅ n + (r0 − p0) ⋅ n = 0     Point on ray and on plane
**       t = ((p0 - l0) ⋅ n) / (r ⋅ n)     Solve for t
**
**    Check that t is not negative (if negative plane is behind the ray)
**    By multiplying t * p we get intersection point
**    and intersection normal is simply plain normal.
*/
static int plane_trace(__global t_obj *obj, t_ray ray, t_hit *hit)
{
    t_real d;
    t_real t;
    t_vec3 n;

	n = dir_from_rot(obj->rot);
	d = dot(n, ray.d);
	if (d > EPSILON)
	{
		t = dot(obj->pos - ray.o, n) / d;
		if (t < 0)
			return (0);
		hit->p = ray.o + ray.d * t;
		hit->n = -n;
		hit->obj = obj;
		hit->uv = get_plane_uv(hit->p, hit->n);
		return (1);
	}
    return (0);
}

static int cone_trace(__global t_obj *obj, t_ray ray, t_hit *hit)
{
	t_real k;
	t_real a;
	t_real b;
	t_real c;
	t_real t0;
	t_real t1;
	t_real d;
	t_real z;
	t_hit cap_hit;

	ray_to_object_space(obj, &ray);

	if(!obj->infinite && disk_trace(VEC(0, 0, 1), VEC(0, 0, 0), obj->radius, &ray, &cap_hit))
	{
		*hit = cap_hit;
		hit->obj = obj;
		hit_to_world_space(obj, hit);
		return (1);
	}
	k = obj->radius / obj->height;
	k *= k;
	a = ray.d.x * ray.d.x + ray.d.y * ray.d.y - k * ray.d.z * ray.d.z;
	b = 2 * (ray.d.x * ray.o.x + ray.d.y * ray.o.y - k * ray.d.z * (ray.o.z - obj->height));
	c = ray.o.x * ray.o.x + ray.o.y * ray.o.y - k * (ray.o.z - obj->height) * (ray.o.z - obj->height);

	if (!solve_quadratic(a, b, c, &t0, &t1))
		return (0);
	if ((t0 < 0. || t1 > 0.) && t1 < t0)
		swap(&t0, &t1);

	if (!obj->infinite)
	{
		z = ray.o.z + ray.d.z * t0;
		if (z < EPSILON || z > obj->height)
		{
			d = dot(VEC(0,0, -1), ray.d);
			if (d > EPSILON)
				if (dot(-ray.o, VEC(0,0,-1)) / d < 0)
					return (0);
			swap(&t0, &t1);
			z = ray.o.z + ray.d.z * t0;
			if (z < EPSILON || z > obj->height)
				return (0);
		}
	}
	if (t0 < EPSILON)
		return (0);

	hit->p = ray.o + ray.d * t0;
	hit->n = normalize(VEC(hit->p.x, hit->p.y, 0));
	hit->obj = obj;
	hit->uv = get_cylinder_uv(hit->p, obj->height, obj->radius);
	hit_to_world_space(obj, hit);
	return (1);
}

static int cylinder_trace(__global t_obj *obj, t_ray ray, t_hit *hit)
{
	t_real a;
	t_real b;
	t_real c;
	t_real t0;
	t_real t1;
	t_hit cap_hit;

	ray_to_object_space(obj, &ray);

	if (!obj->infinite && disk_trace(VEC(0, 0, -1), VEC(0, 0, obj->height), obj->radius, &ray, &cap_hit))
	{
		*hit = cap_hit;
		hit->obj = obj;
		hit_to_world_space(obj, hit);
		return (1);
	}
	else if (!obj->infinite && disk_trace(VEC(0, 0, 1), VEC(0, 0, 0), obj->radius, &ray, &cap_hit))
	{
		*hit = cap_hit;
		hit->obj = obj;
		hit_to_world_space(obj, hit);
		return (1);
	}
	// R(t) = o + td
	// x² + z² = r²
	// (ox+tdx)² + (oz+tdz)² = r²
	// (ox)² + 2oxtdx + (tdx)² + (oz)² + 2oztdz + (tdz)² = r²
	// t²(dx + dz) + 2t(oxdx + ozdz) + (ox)² + (oz)² - r² = 0
	a = ray.d.x * ray.d.x + ray.d.y * ray.d.y;
	b = 2.0 * (ray.d.x * ray.o.x + ray.d.y * ray.o.y);
	c = ray.o.x * ray.o.x + ray.o.y * ray.o.y - obj->radius * obj->radius;

	if (!solve_quadratic(a, b, c, &t0, &t1))
		return (0);

	if (t0 < EPSILON)
		return (0);

	if (!obj->infinite && !(((ray.o.z + ray.d.z * t0) > 0) &&
		((ray.o.z + ray.d.z * t0) < obj->height)))
		return (0);
	hit->p = ray.o + ray.d * t0;
	hit->n = normalize(VEC(hit->p.x, hit->p.y, 0));
	hit->obj = obj;
	hit->uv = get_cylinder_uv(hit->p, obj->height, obj->radius);
	hit_to_world_space(obj, hit);
	return (1);
}

static int paraboloid_trace(__global t_obj *obj, t_ray ray, t_hit *hit)
{
    t_real a;
    t_real b;
    t_real c;
    t_real t0;
    t_real t1;
	t_real k;

	ray_to_object_space(obj, &ray);
	k = obj->height / pow(obj->radius, 2);
	a = k * (ray.d.x * ray.d.x + ray.d.y * ray.d.y);
	b = 2.0 * k * (ray.o.x * ray.d.x + ray.o.y * ray.d.y) - ray.d.z;
	c = k * (ray.o.x * ray.o.x + ray.o.y * ray.o.y) - ray.o.z;

	if (!solve_quadratic(a, b, c, &t0, &t1))
		return (0);
	
	if (t0 < 0 || t0 < EPSILON)
		return (0);

    hit->p = ray.o + ray.d * t0;
	hit->n = normalize(VEC(hit->p.x, hit->p.y, 0));
    hit->obj = obj;
	hit->uv = get_cylinder_uv(hit->p, obj->height, obj->radius);
	hit_to_world_space(obj, hit);
    return (1);
}

static int ellipse_trace(__global t_obj *obj, t_ray ray, t_hit *hit)
{
    t_real a;
    t_real b;
    t_real c;
    t_real t0;
    t_real t1;

	ray_to_object_space(obj, &ray);

	a = (ray.d.x * ray.d.x) / 16.0 + (ray.d.y * ray.d.y) / 16.0 + (ray.d.z * ray.d.z) / 4.0;
	b = 2 * ((ray.o.x * ray.d.x) / 16.0 + (ray.o.y * ray.d.y) / 16.0 + (ray.o.z * ray.d.z) / 4.0);
	c = (ray.o.x * ray.o.x) / 16.0 + (ray.o.y * ray.o.y) / 16.0 + (ray.o.z * ray.o.z) / 4.0 - obj->radius * obj->radius;
	
	if (!solve_quadratic(a, b, c, &t0, &t1))
		return (0);
	
	if (t0 < 0 || t0 <= EPSILON)
		return (0);

    hit->p = ray.o + ray.d * t0;
	hit->n = normalize(hit->p);
    hit->obj = obj;
	hit_to_world_space(obj, hit);
    return (1);
}

static int parabolic_cylinder_trace(__global t_obj *obj, t_ray ray, t_hit *hit)
{
    t_real a;
    t_real b;
    t_real c;
    t_real t0;
    t_real t1;
	t_real k;

	ray_to_object_space(obj, &ray);
	k = 10.0 / pow(obj->radius, 2);

	a = k * ray.d.x * ray.d.x;
	b = 2.0 * k * (ray.o.x * ray.d.x) - 10.0 * ray.d.y;
	c =  k * ray.o.x * ray.o.x - 5.0 * ray.o.y;

	if (!solve_quadratic(a, b, c, &t0, &t1))
		return (0);
	
	if (t0 < 0 || t0 <= EPSILON)
		return (0);

    hit->p = ray.o + ray.d * t0;
	hit->n = normalize(VEC(hit->p.x, hit->p.y, 0));
    hit->obj = obj;
	hit_to_world_space(obj, hit);
    return (1);
}

static int hyperbolic_cylinder_trace(__global t_obj *obj, t_ray ray, t_hit *hit)
{
    t_real a;
    t_real b;
    t_real c;
    t_real t0;
    t_real t1;

	ray_to_object_space(obj, &ray);

	a = ((ray.d.x * ray.d.x) * 0.25) - ((ray.d.y * ray.d.y) * 0.0625);
	b = 2.0 * (((ray.d.x * ray.o.x) * 0.25) - ((ray.d.y * ray.o.y) * 0.0625));
	c = ((ray.o.x * ray.o.x) * 0.25) - ((ray.o.y * ray.o.y) * 0.0625) + 1.0;

	if (!solve_quadratic(a, b, c, &t0, &t1))
		return (0);
	
	if (t0 < 0 || t0 <= EPSILON)
		return (0);

    hit->p = ray.o + ray.d * t0;
	hit->n = normalize(VEC(hit->p.x, hit->p.y, 0));
    hit->obj = obj;
	hit_to_world_space(obj, hit);
    return (1);
}

static int hyperbolic_two_sheets_trace(__global t_obj *obj, t_ray ray, t_hit *hit)
{
    t_real a;
    t_real b;
    t_real c;
    t_real t0;
    t_real t1;

	ray_to_object_space(obj, &ray);

	a = - (ray.d.x * ray.d.x) - (ray.d.y * ray.d.y) + ray.d.z * ray.d.z;
	b = 2.0 * (- (ray.o.x * ray.d.x) - (ray.o.y * ray.d.y) + ray.o.z * ray.d.z);
	c = - (ray.o.x * ray.o.x) - (ray.o.y * ray.o.y) + ray.o.z * ray.o.z - 1.0;

	if (!solve_quadratic(a, b, c, &t0, &t1))
		return (0);
	
	if (t0 < 0 || t0 <= EPSILON)
		return (0);

    hit->p = ray.o + ray.d * t0;
	hit->n = normalize(VEC(hit->p.x, hit->p.y, 0));
    hit->obj = obj;
	hit_to_world_space(obj, hit);
    return (1);
}

static int hyperbolic_paraboloid_trace(__global t_obj *obj, t_ray ray, t_hit *hit)
{
    t_real a;
    t_real b;
    t_real c;
    t_real t0;
    t_real t1;

	ray_to_object_space(obj, &ray);

	a = ((ray.d.x * ray.d.x) * 1.1) - ((ray.d.y * ray.d.y) * 1.0);
	b = 2.0 * ((ray.d.x * ray.o.x) * 1.1) - 2.0 * ((ray.d.y * ray.o.y) * 1.0) - ray.d.z;
	c = ((ray.o.x * ray.o.x) * 1.1) - ((ray.o.y * ray.o.y) * 1.0) - ray.o.z;

	if (!solve_quadratic(a, b, c, &t0, &t1))
		return (0);
	
	if (t0 < 0 || t0 <= EPSILON)
		return (0);

    hit->p = ray.o + ray.d * t0;
	hit->n = normalize(VEC(hit->p.x, hit->p.y, 0));
    hit->obj = obj;
	hit_to_world_space(obj, hit);
    return (1);
}

/*
** b[2] - bounds min and max = height / 2
** the center of the cube is located at the intersection of the diagonals
*/
static int cube_trace(__global t_obj *obj, t_ray ray, t_hit *hit)
{
	t_real	a;
	t_vec3	inv_dir;
	t_vec3	b[2];
	t_real	t1;
	t_real	t2;
	t_real	tmin;
	t_real	tmax;

	ray_to_object_space(obj, &ray);
	a = obj->height / 2;

	tmax = INFINITY;
	tmin = -INFINITY;

	b[0] = VEC(-a, -a, -a);
	b[1] = VEC(a, a, a);

	inv_dir = 1 / ray.d;

	t1 = (b[0].x - ray.o.x) * inv_dir.x;
	t2 = (b[1].x - ray.o.x) * inv_dir.x;
	tmin = min(t1, t2);
	tmax = max(t1, t2);

	t1 = (b[0].y - ray.o.y) * inv_dir.y;
	t2 = (b[1].y - ray.o.y) * inv_dir.y;
	tmin = max(tmin, min(t1, t2));
	tmax = min(tmax, max(t1, t2));

	t1 = (b[0].z - ray.o.z) * inv_dir.z;
	t2 = (b[1].z - ray.o.z) * inv_dir.z;
	tmin = max(tmin, min(t1, t2));
	tmax = min(tmax, max(t1, t2));

	if (tmax < max(tmin, EPSILON) || tmin < EPSILON)
		return (0);

	hit->p = ray.o + ray.d * tmin;

	if (fabs(hit->p.x) > fabs(hit->p.y) && fabs(hit->p.x) > fabs(hit->p.z))
  		hit->n = hit->p.x > 0 ? VEC(1, 0, 0) : VEC(-1, 0, 0);
	if (fabs(hit->p.y) > fabs(hit->p.z) && fabs(hit->p.y) > fabs(hit->p.x))
  		hit->n = hit->p.y > 0 ? VEC(0, 1, 0) : VEC(0, -1, 0);
	if (fabs(hit->p.z) > fabs(hit->p.y) && fabs(hit->p.z) > fabs(hit->p.x))
  		hit->n = hit->p.z > 0 ? VEC(0, 0, 1) : VEC(0, 0, -1);

	hit->obj = obj;
	hit->uv = get_cube_uv(hit->p / a);
	hit_to_world_space(obj, hit);
	return (1);
}

/*
** Check that distance from origin to new hit is smaller than old
** and update old with new in that case.
** Returns 1 if ray is updated
*/
static int update_ray(t_hit *old, t_hit *new, t_ray *ray, int *set)
{
    if (!*set)
    {
        *old = *new;
        *set = 1;
        return (1);
    }
    else if (length(new->p - ray->o) < length(old->p - ray->o))
	{
		*old = *new;
		return (1);
	}
	return (0);
}

static void	sample_textures(t_hit *hit,
		__global uchar* tx_b, __global t_tx_info* txi_b)
{
	hit->diff = hit->obj->mat.diff;
	hit->specular = hit->obj->mat.specular;
	hit->reflection = hit->obj->mat.reflection;
	if (hit->obj->mat.diff_tex_id != -1)
		hit->diff = sample_texture(hit->uv, tx_b, txi_b[hit->obj->mat.diff_tex_id]);
	if (hit->obj->mat.spec_tex_id != -1)
		hit->specular *= sample_texture(hit->uv, tx_b, txi_b[hit->obj->mat.spec_tex_id]).x;
	if (hit->obj->mat.refl_tex_id != -1)
		hit->reflection *= sample_texture(hit->uv, tx_b, txi_b[hit->obj->mat.refl_tex_id]).x;
}

/*
** For each object perform intersection and if intersects set hit
** for the first time, later on hit choose which is closest
** and update hit if new one is closest.
** Returns index of object hit or -1 if none hit
*/
t_int	intersect(__global t_obj *scene, size_t size, t_ray *ray, t_hit *hit,
			__global uchar* tx_b, __global t_tx_info* txi_b)
{
    t_hit	tmp;
    int		got_hit;
    int		set;
    int		index;

    if (!scene || !size || !ray || !hit)
    	return (-1);
	*hit = (t_hit){0};
    set = 0;
	index = -1;
    while (size--)
    {
		tmp = (t_hit){0};
		got_hit = 0;
        if (IS_PLN(&scene[size]))
            got_hit = plane_trace(&scene[size], *ray, &tmp);
        else if (IS_SPH(&scene[size]))
            got_hit = sphere_trace(&scene[size], *ray, &tmp);
        else if (IS_CYL(&scene[size]))
            got_hit = cylinder_trace(&scene[size], *ray, &tmp);
        else if (IS_CON(&scene[size]))
            got_hit = cone_trace(&scene[size], *ray, &tmp);
        else if (IS_CUB(&scene[size]))
            got_hit = cube_trace(&scene[size], *ray, &tmp);
		else if (IS_PAR(&scene[size]))
			got_hit = paraboloid_trace(&scene[size], *ray, &tmp);
		else if (IS_PCL(&scene[size]))
			got_hit = parabolic_cylinder_trace(&scene[size], *ray, &tmp);
		else if (IS_ELL(&scene[size]))
			got_hit = ellipse_trace(&scene[size], *ray, &tmp);
		else if (IS_HCL(&scene[size]))
			got_hit = hyperbolic_cylinder_trace(&scene[size], *ray, &tmp);
		else if (IS_HTS(&scene[size]))
			got_hit = hyperbolic_two_sheets_trace(&scene[size], *ray, &tmp);
		else if (IS_HPR(&scene[size]))
			got_hit = hyperbolic_paraboloid_trace(&scene[size], *ray, &tmp);
        if (got_hit && update_ray(hit, &tmp, ray, &set))
			index = size;
    }
    if (index != -1)
		sample_textures(hit, tx_b, txi_b);
    return (index);
}

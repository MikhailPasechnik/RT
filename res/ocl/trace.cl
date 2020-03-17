#include "rt.hcl"

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
	if (discriminant <= EPSILON)
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
	t_mat4 inv_object_space;

	m4_identity(&inv_object_space);
	m4_set_rotation(&inv_object_space, obj->rot);
	inv_object_space = m4_inv(&inv_object_space);
	ray->o -= obj->pos;
	ray->o = m4_mul_vec3(&inv_object_space, &ray->o);
	ray->d = m4_mul_vec3(&inv_object_space, &ray->d);
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
    t_vec3 v;
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
	if (t0 < 0. || t1 > 0. && t1 < t0)
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
	if (t0 <= EPSILON)
		return (0);

	hit->p = ray.o + ray.d * t0;
	hit->n = normalize(VEC(hit->p.x, hit->p.y, 0));
	hit->obj = obj;
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

	if (t0 <= EPSILON)
		return (0);

	if (!obj->infinite && !(((ray.o.z + ray.d.z * t0) >= 0) &&
		((ray.o.z + ray.d.z * t0) <= obj->height)))
		return (0);
	hit->p = ray.o + ray.d * t0;
	hit->n = normalize(VEC(hit->p.x, hit->p.y, 0));
	hit->obj = obj;
	hit_to_world_space(obj, hit);
	return (1);
}

static int cube_trace(__global t_obj *obj, t_ray ray, t_hit *hit)
{
	return (0);
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

/*
** For each object perform intersection and if intersects set hit
** for the first time, later on hit choose which is closest
** and update hit if new one is closest.
** Returns index of object hit or -1 if none hit
*/
t_int	intersect(__global t_obj *scene, size_t size, t_ray *ray, t_hit *hit)
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
        if (got_hit && update_ray(hit, &tmp, ray, &set))
			index = size;
    }
    return (index);
}

#include "rt.hcl"
t_vec3 dir_from_rot(t_vec3 rot)
{
	t_vec3 dir;

	dir.x = sin(radians(rot.z));
	dir.y = -(sin(radians(rot.x)) * cos(radians(rot.z)));
	dir.z = cos(radians(rot.x)) * cos(radians(rot.y));
	return (dir);
}

static inline t_hit *sphere_inter(__global t_obj *obj, t_ray *ray, t_hit *hit)
{
//	float a = dot(r.direction(), r.direction());
//	float b = 2.0 * dot(oc, r.direction());
//	float c = dot(oc,oc) - radius*radius;

    t_vec3 L;
    t_real tca;
    t_real thc;
    t_real t0;
    t_real t1;

    L = obj->pos - ray->orig;
    tca = dot(L, ray->dir);
    if (tca < 0)
        return (NULL);
    thc = dot(L, L) - tca * tca;
    if (thc > obj->radius)
        return (NULL);
    t0 = sqrt(obj->radius - thc);
    t1 = tca + t0;
    t0 = tca - t0;
    if (t1 < 0 && t0 < 0)
        return (NULL);
    t0 = t0 > t1 && t1 > 0 ? t1 : t0;
    hit->pos = ray->orig + ray->dir * t0;
    hit->norm = normalize(hit->pos - obj->pos);
    hit->obj = obj;
    return (hit);
}

static inline t_hit *plane_inter(__global t_obj *obj, t_ray *ray, t_hit *hit)
{
    t_real d;
    t_vec3 v;
    t_real t;

    d = dot(ray->dir, obj->rot);
    if (d > EPSILON)
        return (NULL);
    t = dot(ray->orig - obj->pos, ray->dir) / d;
    if (t < 0)
        return (NULL);
    hit->pos = ray->orig + ray->dir * t;
    hit->norm = normalize(hit->pos - obj->pos);
    hit->obj = obj;
    return (hit);
}

static inline t_hit *cube_inter(__global t_obj *obj, t_ray *ray, t_hit *hit)
{
    return (NULL);
}

static inline t_hit *cone_inter(__global t_obj *obj, t_ray *ray, t_hit *hit)
{
    return (NULL);
}

static void swap(t_real *a, t_real *b)
{
	t_real t;

	t = *a;
	*a = *b;
	*b = t;
}

t_int solve_quadratic(
		t_real a,
		t_real b,
		t_real c,
		t_real *t0,
		t_real *t1)
{
	// Find quadratic discriminant
	float discriminant = b * b - 4.0 * a * c;
	if (discriminant < EPSILON)
		return (0);
	float rootDiscriminant = sqrt(discriminant);

	// Compute quadratic _t_ values
	float q;
	if (b < 0)
		q = -.5f * (b - rootDiscriminant);
	else
		q = -.5f * (b + rootDiscriminant);
	*t0 = q / a;
	*t1 = c / q;
	if (*t0 > *t1)
		swap(t0, t1);
	return (1);
}
void pv(t_vec3 v, t_vec3 b)
{
	printf("------{% .2f % .2f % .2f} {% .2f % .2f % .2f}------\n", v.x, v.y, v.z, b.x, b.y, b.z);
}
static inline t_hit *cylinder_inter(__global t_obj *obj, t_ray *ray, t_hit *hit)
{

	t_vec3 p0;
	t_vec3 r;
	t_vec3 t;
	t_vec3 dir;

	p0 = ray->orig - obj->pos;

	t_mat4 D;
	t_mat4 INV;
	r = obj->rot;
	t = obj->pos;
//	printf( "%f ", deg2rad(r.z));
	m4_identity(&D);
	D.sF = 1;
	m4_set_rotation(&D, obj->rot);
//	m4_set_translate(&D, &t);
	INV = m4_inv(&D);
	dir = normalize(m4_mul_vec3(&INV, &ray->dir));
//	dir = ray->dir;
	 pv(ray->dir, dir);
//	p0 =  m4_mul_vec3(&D, &ray->orig);
	// R(t) = o + td
	// x² + z² = r²
	// (ox+tdx)² + (oz+tdz)² = r²
	// (ox)² + 2oxtdx + (tdx)² + (oz)² + 2oztdz + (tdz)² = r²
	// t²(dx + dz) + 2t(oxdx + ozdz) + (ox)² + (oz)² - r² = 0
	double a = dir.x * dir.x + dir.z * dir.z;
	double b = 2.0 * (dir.x * p0.x + dir.z * p0.z);
	double c = p0.x * p0.x + p0.z * p0.z - obj->radius * obj->radius;
//
//	double delta = b*b - a*c;
//
//	//use epsilon because of computation errors between doubles
//	double epsilon = 0.00000001;
//	// delta < 0 means no intersections
//	if (delta < epsilon)
//		return (NULL);

	t_real t0;
	t_real t1;
	if (!solve_quadratic(a, b, c, &t0, &t1))
		return (NULL);
//
////	 t<0 means the intersection is behind the ray origin
////	 which we don't want
//	if (t0 <= EPSILON)
//		return (NULL);
//

	// double y = p0.y+t*ray->dir.y;
	// check if we intersect one of the bases
//	if (y > height+epsilon || y < -epsilon) {
//		double dist;
//		bool b1 = intersect_base (ray, center2, dist);
//		if(b1) t=dist;
//		bool b2 = intersect_base (ray, center, dist);
//		if(b2 && dist>epsilon && t>=dist)
//		t=dist;
//		return b1 || b2;
//	}
	hit->pos = ray->orig + ray->dir * t0;
	hit->norm = normalize(hit->pos - obj->pos);
	hit->obj = obj;
	return (hit);
}

/*
** Check that distance from origin to new hit is smaller than old
** and update old with new in that case
*/
static inline void update_ray(t_hit *old, t_hit *new, t_ray *ray, int *set)
{
    if (!*set)
    {
        *old = *new;
        *set = 1;
    }
    else if (length(new->pos - ray->orig) < length(old->pos - ray->orig))
        *old = *new;
}

/*
** For each object perform intersection and if intersects set hit
** for the first time, later on hit choose which is closest
** and update hit if new one is closest
*/
t_hit	*intersect(__global t_obj *scene, size_t size, t_ray *ray, t_hit *hit)
{
    t_hit	t;
    t_hit	*new;
    int		set;

    set = 0;
    while (size--)
    {
        new = NULL;
        if (IS_PLN(&scene[size]))
            new = plane_inter(&scene[size], ray, &t);
        else if (IS_SPH(&scene[size]))
            new = sphere_inter(&scene[size], ray, &t);
        else if (IS_CYL(&scene[size]))
            new = cylinder_inter(&scene[size], ray, &t);
        else if (IS_CON(&scene[size]))
            new = cone_inter(&scene[size], ray, &t);
        else if (IS_CUB(&scene[size]))
            new = cube_inter(&scene[size], ray, &t);
        if (new)
            update_ray(hit, new, ray, &set);
    }
    return (set ? hit : NULL);
}

#include "rt.hcl"



static inline t_hit *disk_inter(t_vec3 dir, t_vec3 pos, t_real radius, t_ray
*ray, t_hit *hit)
{
	t_vec3 hit_pos;
	t_real d;
    t_real t;

	d = dot(dir, ray->dir);
	if (d > EPSILON)
		return (NULL);
	t = dot(pos - ray->orig, dir) / d;
    if (t < 0)
        return (NULL);
	hit_pos = ray->orig + ray->dir * t;

	float d2 = dot(hit_pos - pos, hit_pos - pos);
	if (sqrt(d2) > radius)
		return (NULL);
	hit->pos = hit_pos;
	hit->norm = dir;
    return (hit);
}

/*
** Sphere intersections:
**    First project ray normal onto line between ray origin and sphere center:
**       Check that it is not behind us ignoring radius
**       because if sphere overlaps we are hitting its back side.
**       The dot product between the ray and the plane normal will be > 0
**       if they are facing each other, and < 0 if looking away.
**
**       Then using Pythagorean theorem we check that we are not overshooting sphere.
**
**       Finally using point we found and Pythagorean theorem we find to intersection
**       candidates from whom we choose the closest one.
**
**       Sphere normal at intersection computed by normalising difference
**       between sphere center and intersection point.
*/
static inline t_hit *sphere_inter(__global t_obj *obj, t_ray *ray, t_hit *hit)
{
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
static inline t_hit *plane_inter(__global t_obj *obj, t_ray *ray, t_hit *hit)
{
    t_real d;
    t_vec3 v;
    t_real t;
    t_vec3 n;

	n = dir_from_rot(obj->rot);
	d = dot(n, ray->dir);
	if (d > EPSILON)
		return (NULL);
	t = dot(obj->pos - ray->orig, n) / d;
    if (t < 0)
        return (NULL);
	hit->pos = ray->orig + ray->dir * t;
	hit->norm = n;
	hit->obj = obj;
    return (hit);
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
	if (discriminant <= EPSILON)
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

void ray_to_object_space(__global t_obj *obj, t_ray *ray, t_vec3 *dir, t_vec3 *pos)
{
	t_mat4 inverse_os;

	m4_identity(&inverse_os);
	m4_set_rotation(&inverse_os, obj->rot);
	inverse_os = m4_inv(&inverse_os);
	*pos = ray->orig - obj->pos;
	*pos =  m4_mul_vec3(&inverse_os, pos);
	*dir = normalize(m4_mul_vec3(&inverse_os, &ray->dir));
}

void hit_to_world_space(__global t_obj *obj, t_hit *hit)
{
	t_mat4 object_space;

	m4_identity(&object_space);
	m4_set_rotation(&object_space, obj->rot);
	hit->norm = m4_mul_vec3(&object_space, &hit->norm);
	hit->pos =  m4_mul_vec3(&object_space, &hit->pos);
	hit->pos += obj->pos;
}

static inline t_hit *cone_inter(__global t_obj *obj, t_ray *ray, t_hit *hit)
{
	t_vec3 pos;
	t_vec3 dir;

	ray_to_object_space(obj, ray, &dir, &pos);
//

	t_hit cap_hit;

	t_ray r;
	r.orig = pos;
	r.dir = dir;

	if(disk_inter(VEC(0, 0, -1), VEC(0, 0, 0), obj->radius, &r, &cap_hit))
	{
		hit->obj = obj;
		hit->pos = cap_hit.pos;
		hit->norm = VEC(0, 0, -1);
		hit_to_world_space(obj, hit);
		return (hit);
	}

	float k = obj->radius / obj->height;
	k = k * k;

//	t_vec3 p1 = VEC(obj->pos.x + obj->radius, obj->pos.y, obj->pos.z);
//	t_vec3 p2 = VEC(obj->pos.x, obj->pos.y + obj->height, obj->pos.z);
//	double d = distance(p2, p1);
//	t_real cos_a = obj->height / d;
//	t_real sin_a = obj->radius / d;
//
//	double a = cos_a * dir.x*dir.x+cos_a*dir.z*dir.z-sin_a*dir.y*dir.y;
//	double b = cos_a*dir.x*pos.x +cos_a*dir.z*pos.z-sin_a*dir.y*pos.y;
//	double c = cos_a*pos.x*pos.x+cos_a*pos.z*pos.z-sin_a*pos.y*pos.y;
//
	double a = dir.x * dir.x + dir.y * dir.y - k * dir.z * dir.z;
	double b = 2 * (dir.x * pos.x + dir.y * pos.y -
			k * dir.z * (pos.z - obj->height));
	double c =  pos.x * pos.x + pos.y * pos.y -
			k * (pos.z - obj->height) * (pos.z - obj->height);

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
	if (t0 < 0. || t1 > 0. && t1 < t0)
		swap(&t0, &t1);
//	if (t0 > 0 && t1 > 0 && t0 < t1)
//		printf("pos01 t0: %f t1: %f\n", t0, t1);
//
//	////	 t<0 means the intersection is behind the ray origin
////	////	 which we don't want
	if (t0 <= EPSILON)
		return (NULL);

	t_vec3 pp = (pos + dir * t0);
//	t_vec3 cp = pos + dir * t0;
//	float z = dot(cp, VEC(0, 0, 1));
//	printf("Z: %f t0: %f t1: %f\n", z, t0, t1);


	if ((pp.z < EPSILON || pp.z > obj->height))
	{
		swap(&t0, &t1);
		pp = (pos + dir * t0);
		if ((pp.z < EPSILON || pp.z > obj->height))
			return (NULL);
	}




	hit->pos = pos + dir * t0;
	hit->norm = normalize(VEC(hit->pos.x, hit->pos.y, sin(obj->height / obj->radius)));
//	hit->norm /= obj->height / obj->radius;
//	hit->norm.z = obj->height / obj->radius;
	hit->obj = obj;
	hit_to_world_space(obj, hit);
//	hit->pos = ray->orig + ray->dir * t0;
	return (hit);
}



void pv(t_vec3 v, t_vec3 b)
{
//	printf("------{% .2f % .2f % .2f} {% .2f % .2f % .2f}------\n", v.x, v.y, v.z, b.x, b.y, b.z);
}

/*
 * This breaks into two distinct pieces: testing collisions against the endcaps, and testing collisions against the body of the cylinder.

The simplest way to handle both is to first transform your way into object space — the ideal 'object space' for a cylinder is with the origin at the center of one endcap and one axis (for concreteness' sake, we'll say the Z axis) running along the 'body' of the cylinder, orthogonal to the endcap planes. In this space, your cylinder is then a pair of discs of radius R in the xy plane, capping a cylinder that runs from z=0 to z=L.

To intersect the ray with one endcap, then, you need to find the point on your ray where it intersects the xy plane: assuming that your ray's equation is r(t)=r0+d*t (I'm using boldface here for vector quantities), then by solving rz(t)=0 for t, you find t=-(r0z/dz) (note that this breaks down if dz=0; in other words, if your ray is parallel to the xy-plane. In that case, you can skip the endcap test and just test against the cylinder, along with a check to make sure that r0z is between 0 and L). (Similarly, if you were trying to intersect with the z=L endcap, you'd find t=(L-r0z)/dz ). Plugging this value of t into your ray equation then gives you a point p where the ray intersects the plane of the endcap; now you just need to test whether this point is within your disc or not - in other words, whether px2+py2 ≤ R2.

Testing against the body of the cylinder works similarly, but is a bit more complicated: in this case, you'll project your ray down to the 2d plane (since we're working in object coordinates, this is as simple as dropping the z component of your ray equation — you can see why these coordinates are so useful!) and then doing a 2d line-circle intersection: essentially you want to find the points where |rxy(t)|2=R2 (here rxy(t) is the ray equation 'projected' down to the xy plane by dropping the z component); this equation is just a quadratic in t, and you can solve it for the two possible values of t. One big caveat, though: once you find the two values of t that solve the equation (and note that there may be none, which means that your ray doesn't intersect the cylinder at all), you'll have to plug them back into your original equation to make sure the corresponding z values fall in the 0..L range.

Finally, you'll have (up to) four distinct t values: the two possible intersections with the endcaps, and the two possible intersections with the sides of the cylinder. (Of course, in practice there can only be two, but that's a separate matter). Just choose the smallest of these that's greater than zero, and that's your intersection point.

 * */
static inline t_hit *cylinder_inter(__global t_obj *obj, t_ray *ray, t_hit *hit)
{

	t_vec3 pos;
	t_vec3 dir;

	ray_to_object_space(obj, ray, &dir, &pos);
	t_hit cap_hit;

	t_ray r;
	r.orig = pos;
	r.dir = dir;

	if(disk_inter(VEC(0, 0, -1), VEC(0, 0, 0), obj->radius, &r, &cap_hit))
	{
		hit->obj = obj;
		hit->pos = cap_hit.pos;
		hit->norm = VEC(0, 0, -1);
		hit_to_world_space(obj, hit);
		return (hit);
	}
	if(disk_inter(VEC(0, 0, 1), VEC(0, 0, obj->height), obj->radius, &r,
			&cap_hit))
	{
		hit->obj = obj;
		hit->pos = cap_hit.pos;
		hit->norm = VEC(0, 0, 1);
		hit_to_world_space(obj, hit);
		return (hit);
	}
	// R(t) = o + td
	// x² + z² = r²
	// (ox+tdx)² + (oz+tdz)² = r²
	// (ox)² + 2oxtdx + (tdx)² + (oz)² + 2oztdz + (tdz)² = r²
	// t²(dx + dz) + 2t(oxdx + ozdz) + (ox)² + (oz)² - r² = 0
	double a = dir.x * dir.x + dir.y * dir.y;
	double b = 2.0 * (dir.x * pos.x + dir.y * pos.y);
	double c = pos.x * pos.x + pos.y * pos.y - obj->radius * obj->radius;

	t_real t0;
	t_real t1;
	if (!solve_quadratic(a, b, c, &t0, &t1))
		return (NULL);


	if (t0 <= EPSILON)
		return (NULL);

	if (((pos.z + dir.z * t0) >= 0) &&
		((pos.z + dir.z * t0) <= obj->height))
	{
		hit->pos = pos + dir * t0;
		hit->norm = normalize(VEC(hit->pos.x, hit->pos.y, 0));
		hit->obj = obj;
		hit_to_world_space(obj, hit);
		return (hit);
	}
	return (NULL);
}
static inline t_hit *cube_inter(__global t_obj *obj, t_ray *ray, t_hit *hit)
{
	return (NULL);
}
/*
** Check that distance from origin to new hit is smaller than old
** and update old with new in that case.
** Returns 1 if ray is updated
*/
static inline int update_ray(t_hit *old, t_hit *new, t_ray *ray, int *set)
{
    if (!*set)
    {
        *old = *new;
        *set = 1;
        return (1);
    }
    else if (length(new->pos - ray->orig) < length(old->pos - ray->orig))
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
    t_hit	*new;
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
        new = NULL;
        if (IS_PLN(&scene[size]))
            new = plane_inter(&scene[size], ray, &tmp);
        else if (IS_SPH(&scene[size]))
            new = sphere_inter(&scene[size], ray, &tmp);
        else if (IS_CYL(&scene[size]))
            new = cylinder_inter(&scene[size], ray, &tmp);
        else if (IS_CON(&scene[size]))
            new = cone_inter(&scene[size], ray, &tmp);
        else if (IS_CUB(&scene[size]))
            new = cube_inter(&scene[size], ray, &tmp);
        if (new && update_ray(hit, new, ray, &set))
			index = size;
    }
    return (index);
}

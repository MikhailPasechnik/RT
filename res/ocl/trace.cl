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

	t_vec3 p0;
	t_vec3 r;
	t_vec3 t;
	t_vec3 dir;

	p0 = ray->orig - obj->pos;

	t_mat4 R;
	t_mat4 INV;
	r = obj->rot;
	t = obj->pos;
	//	printf( "%f ", deg2rad(r.z));
	m4_identity(&R);
	m4_set_rotation(&R, obj->rot);
	//	m4_set_translate(&D, &t);
	INV = m4_inv(&R);
	dir = normalize(m4_mul_vec3(&INV, &ray->dir));
	//	dir = ray->dir;
	//	p0 =  m4_mul_vec3(&D, &ray->orig);
	// R(t) = o + td
	// x² + z² = r²
	// (ox+tdx)² + (oz+tdz)² = r²
	// (ox)² + 2oxtdx + (tdx)² + (oz)² + 2oztdz + (tdz)² = r²
	// t²(dx + dz) + 2t(oxdx + ozdz) + (ox)² + (oz)² - r² = 0
	// t²(dx + dz) + 2t(oxdx + ozdz) + (ox)² + (oz)² - r² = 0
	float A = p0.x;
	float B = p0.z;
	float D = obj->height - p0.y;

	float tan = (obj->radius / obj->height) * (obj->radius / obj->height);
	double a = (dir.x * dir.x) + (dir.z * dir.z) - (tan *(dir.y * dir.y));
	double b = (2.0 * A *dir.x) + (2.0 * B *dir.z) +  (2* tan * D * dir.y);
	double c = (A*A) + (B*B) - tan * (D * D);
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

/*
 * This breaks into two distinct pieces: testing collisions against the endcaps, and testing collisions against the body of the cylinder.

The simplest way to handle both is to first transform your way into object space — the ideal 'object space' for a cylinder is with the origin at the center of one endcap and one axis (for concreteness' sake, we'll say the Z axis) running along the 'body' of the cylinder, orthogonal to the endcap planes. In this space, your cylinder is then a pair of discs of radius R in the xy plane, capping a cylinder that runs from z=0 to z=L.

To intersect the ray with one endcap, then, you need to find the point on your ray where it intersects the xy plane: assuming that your ray's equation is r(t)=r0+d*t (I'm using boldface here for vector quantities), then by solving rz(t)=0 for t, you find t=-(r0z/dz) (note that this breaks down if dz=0; in other words, if your ray is parallel to the xy-plane. In that case, you can skip the endcap test and just test against the cylinder, along with a check to make sure that r0z is between 0 and L). (Similarly, if you were trying to intersect with the z=L endcap, you'd find t=(L-r0z)/dz ). Plugging this value of t into your ray equation then gives you a point p where the ray intersects the plane of the endcap; now you just need to test whether this point is within your disc or not - in other words, whether px2+py2 ≤ R2.

Testing against the body of the cylinder works similarly, but is a bit more complicated: in this case, you'll project your ray down to the 2d plane (since we're working in object coordinates, this is as simple as dropping the z component of your ray equation — you can see why these coordinates are so useful!) and then doing a 2d line-circle intersection: essentially you want to find the points where |rxy(t)|2=R2 (here rxy(t) is the ray equation 'projected' down to the xy plane by dropping the z component); this equation is just a quadratic in t, and you can solve it for the two possible values of t. One big caveat, though: once you find the two values of t that solve the equation (and note that there may be none, which means that your ray doesn't intersect the cylinder at all), you'll have to plug them back into your original equation to make sure the corresponding z values fall in the 0..L range.

Finally, you'll have (up to) four distinct t values: the two possible intersections with the endcaps, and the two possible intersections with the sides of the cylinder. (Of course, in practice there can only be two, but that's a separate matter). Just choose the smallest of these that's greater than zero, and that's your intersection point.

 * */
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

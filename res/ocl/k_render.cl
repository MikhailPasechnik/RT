# include "../../include/obj.h"
# define EPSILON 1e-16
# ifndef NULL
# define NULL ((void *)0)
# endif

# define COLOR(r, g, b, a) ((t_color){r, g, b})
# define VEC(x, y, z)((t_vec3){x, y, z})

typedef float		t_real;
typedef float16		t_mat4;
typedef float3		t_vec3;
typedef int			t_int;
typedef uint		t_uint;
typedef float3		t_color;

typedef struct	s_hit {
	t_vec3	p;
	t_vec3	n;
	__global t_obj	*obj;
}				t_hit;

t_real deg2rad(t_real deg)
{
    return deg * (M_PI / 180);
}

t_mat4 m4_mul(t_mat4 *m, t_mat4 *n)
{
    t_mat4 result = (t_mat4){
    m->s0 * n->s0 + m->s1 * n->s4 + m->s2 * n->s8 + m->s3 * n->sC,
    m->s0 * n->s1 + m->s1 * n->s5 + m->s2 * n->s9 + m->s3 * n->sD,
    m->s0 * n->s2 + m->s1 * n->s6 + m->s2 * n->sA + m->s3 * n->sE,
    m->s0 * n->s3 + m->s1 * n->s7 + m->s2 * n->sB + m->s3 * n->sF,
    m->s4 * n->s0 + m->s5 * n->s4 + m->s6 * n->s8 + m->s7 * n->sC,
    m->s4 * n->s1 + m->s5 * n->s5 + m->s6 * n->s9 + m->s7 * n->sD,
    m->s4 * n->s2 + m->s5 * n->s6 + m->s6 * n->sA + m->s7 * n->sE,
    m->s4 * n->s3 + m->s5 * n->s7 + m->s6 * n->sB + m->s7 * n->sF,
    m->s8 * n->s0 + m->s9 * n->s4 + m->sA * n->s8 + m->sB * n->sC,
    m->s8 * n->s1 + m->s9 * n->s5 + m->sA * n->s9 + m->sB * n->sD,
    m->s8 * n->s2 + m->s9 * n->s6 + m->sA * n->sA + m->sB * n->sE,
    m->s8 * n->s3 + m->s9 * n->s7 + m->sA * n->sB + m->sB * n->sF,
    m->sC * n->s0 + m->sD * n->s4 + m->sE * n->s8 + m->sF * n->sC,
    m->sC * n->s1 + m->sD * n->s5 + m->sE * n->s9 + m->sF * n->sD,
    m->sC * n->s2 + m->sD * n->s6 + m->sE * n->sA + m->sF * n->sE,
    m->sC * n->s3 + m->sD * n->s7 + m->sE * n->sB + m->sF * n->sF};
    return (result);
}

t_vec3 m4_mul_vec3(t_mat4 *m, t_vec3 *v)
{
    t_real	w;
    t_vec3	out;

    w = v->x * m->s3 + v->y * m->s7 +
        v->z * m->sB + m->sF;
    out.x = (
         v->x * m->s0 +
         v->y * m->s4 +
         v->z * m->s8 + m->sC) / w;
    out.y = (
         v->x * m->s1 +
         v->y * m->s5 +
         v->z * m->s9 + m->sD) / w;
    out.z = (
         v->x * m->s2 +
         v->y * m->s6 +
         v->z * m->sA + m->sE) / w;
    return (out);
}

void    m4_identity(t_mat4 *m)
{
    *m = (t_mat4)(0);
    m->s0 = 1;
    m->s5 = 1;
    m->sA = 1;
    m->sF = 1;
}
/* M.s0, M.s1, M.s2, M.s3
** M.s4, M.s5, M.s6, M.s7
** M.s8, M.s9, M.sA, M.sB
** M.sC, M.sD, M.sE, M.sF
*/
void	m4_set_translate(t_mat4 *m, t_vec3 t)
{
    m->sC = t.x;
    m->sD = t.y;
    m->sE = t.z;
}

void	m4_set_rotation(t_mat4 *m, t_vec3 r)
{
    t_real	cos_v[3];
    t_real	sin_v[3];

    cos_v[2] = cos(deg2rad(r.z));
    cos_v[1] = cos(deg2rad(r.y));
    cos_v[0] = cos(deg2rad(r.x));
    sin_v[2] = sin(deg2rad(r.z));
    sin_v[1] = sin(deg2rad(r.y));
    sin_v[0] = sin(deg2rad(r.x));
    m->s0 = cos_v[2] * cos_v[1];
    m->s1 = sin_v[2] * cos_v[1];
    m->s2 = -sin_v[1];
    m->s4 = -sin_v[2] * cos_v[0] + cos_v[2] * sin_v[1] * sin_v[0];
    m->s5 = cos_v[2] * cos_v[0] + sin_v[2] * sin_v[1] * sin_v[0];
    m->s6 = cos_v[1] * sin_v[0];
    m->s8 = -sin_v[2] * -sin_v[0] + cos_v[2] * sin_v[1] * cos_v[0];
    m->s9 = cos_v[2] * -sin_v[0] + sin_v[2] * sin_v[1] * cos_v[0];
    m->sA = cos_v[1] * cos_v[0];
}
/* M.s0, M.s1, M.s2, M.s3
** M.s4, M.s5, M.s6, M.s7
** M.s8, M.s9, M.sA, M.sB
** M.sC, M.sD, M.sE, M.sF
*/
static void		coefficient(t_mat4 *m, t_real *out)
{
	out[0] = m->s6 * m->sB - m->s7 * m->sA;
	out[1] = m->s6 * m->sF - m->s7 * m->sE;
	out[3] = m->sA * m->sF - m->sB * m->sE;
	out[4] = m->s9 * m->sF - m->sB * m->sD;
	out[5] = m->s5 * m->sF - m->s7 * m->sD;
	out[6] = m->s5 * m->sB - m->s7 * m->s9;
	out[7] = m->s9 * m->sE - m->sA * m->sD;
	out[8] = m->s5 * m->sE - m->s6 * m->sD;
	out[9] = m->s5 * m->sA - m->s6 * m->s9;
	out[10] = m->s8 * m->sF - m->sB * m->sC;
	out[11] = m->s8 * m->sE - m->sA * m->sC;
	out[12] = m->s8 * m->sD - m->s9 * m->sC;
	out[13] = m->s4 * m->sF - m->s7 * m->sC;
	out[14] = m->s4 * m->sE - m->s6 * m->sC;
	out[15] = m->s4 * m->sB - m->s7 * m->s8;
	out[16] = m->s4 * m->sA - m->s6 * m->s8;
	out[17] = m->s4 * m->sD - m->s5 * m->sC;
	out[18] = m->s4 * m->s9 - m->s5 * m->s8;
}

static void		inv_apply(const t_mat4 *m,
							 const t_real *c, t_mat4 *o, t_real d)
{
	o->s0 = d * (m->s5 * c[3] - m->s6 * c[4] + m->s7 * c[7]);
	o->s1 = d * -(m->s1 * c[3] - m->s2 * c[4] + m->s3 * c[7]);
	o->s2 = d * (m->s1 * c[1] - m->s2 * c[5] + m->s3 * c[8]);
	o->s3 = d * -(m->s1 * c[0] - m->s2 * c[6] + m->s3 * c[9]);
	o->s4 = d * -(m->s4 * c[3] - m->s6 * c[10] + m->s7 * c[11]);
	o->s5 = d * (m->s0 * c[3] - m->s2 * c[10] + m->s3 * c[11]);
	o->s6 = d * -(m->s0 * c[1] - m->s2 * c[13] + m->s3 * c[14]);
	o->s7 = d * (m->s0 * c[0] - m->s2 * c[15] + m->s3 * c[16]);
	o->s8 = d * (m->s4 * c[4] - m->s5 * c[10] + m->s7 * c[12]);
	o->s9 = d * -(m->s0 * c[4] - m->s1 * c[10] + m->s3 * c[12]);
	o->sA = d * (m->s0 * c[5] - m->s1 * c[13] + m->s3 * c[17]);
	o->sB = d * -(m->s0 * c[6] - m->s1 * c[15] + m->s3 * c[18]);
	o->sC = d * -(m->s4 * c[7]- m->s5 * c[11] + m->s6 * c[12]);
	o->sD = d * (m->s0 * c[7]- m->s1 * c[11] + m->s2 * c[12]);
	o->sE = d * -(m->s0 * c[8] - m->s1 * c[14] + m->s2 * c[17]);
	o->sF = d * (m->s0 * c[9] - m->s1 * c[16] + m->s2 * c[18]);
}

t_mat4			m4_inv(t_mat4 *m)
{
	t_mat4 out;
	t_real d;
	t_real c[19];
	coefficient(m, c);
	d = m->s0 * (m->s5 * c[3] - m->s6 * c[4] + m->s7 * c[7])
		- m->s1 * (m->s4 * c[3] - m->s6 * c[10] + m->s7 * c[11])
		+ m->s2 * (m->s4 * c[4] - m->s5 * c[10] + m->s7 * c[12])
		- m->s3 * (m->s4 * c[7] - m->s5 * c[11] + m->s6 * c[12]);
	d = 1 / d;
	inv_apply(m, c, &out, d);
	return (out);
}

void print_render_args(t_options *options, t_cam* camera,
        __global t_obj* scene, __global t_light* lights)
{
    printf("Options:\n"
        "\twidth: %d\n"
        "\theight: %d\n"
        "\tobj_count: %d\n"
        "\tlight_count: %d\n",
        options->width,
        options->height,
        options->obj_count,
        options->light_count
    );
    printf("Camera:\n"
        "\tfov: %f\n"
        "\tpos: %f %f %f\n",
        camera->fov,
		camera->mtx.sC,
		camera->mtx.sD,
		camera->mtx.sE
    );
    int i = options->obj_count;
    while (i < options->obj_count)
    {
        printf("Obj: id: %d radius: %f pos: {%f %f %f}\n",
            scene[i].id, scene[i].radius,
            scene[i].pos.x,
            scene[i].pos.y,
            scene[i].pos.z
        );
        i++;
    }
}

t_vec3 cam_view_vec3(t_mat4 *m, t_vec3 *v)
{
	t_real	w;
	t_vec3	out;

	w = v->x * m->s3 + v->y * m->s7 +
		v->z * m->sB + m->sF;
	out.x = (
					v->x * m->s0 +
					v->y * m->s4 +
					v->z * m->s8) / w;
	out.y = (
					v->x * m->s1 +
					v->y * m->s5 +
					v->z * m->s9) / w;
	out.z = (
					v->x * m->s2 +
					v->y * m->s6 +
					v->z * m->sA) / w;
	return (out);
}

t_ray   new_camera_ray(t_options *op, t_cam *cam, uint2 pixel)
{
	t_ray ray;
	t_real width;
	t_real height;
	t_real scale;
	t_vec3 dir;

	width  = op->width;
	height = op->height;
	scale  = tan(radians(cam->fov * 0.5));
	dir.x = (2 * (pixel.x + 0.5) / width - 1) * (width / height) * scale;
	dir.y = (1 - 2 * (pixel.y + 0.5) / height) * scale;
	dir.z = -1;
	ray.o = VEC(cam->mtx.sC, cam->mtx.sD, cam->mtx.sE);
	ray.d = normalize(cam_view_vec3(&cam->mtx, &dir));
	return (ray);
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

t_vec3 dir_from_rot(t_vec3 rot)
{
	t_vec3 dir;

	dir.x = sin(radians(rot.z));
	dir.y = -(sin(radians(rot.x)) * cos(radians(rot.z)));
	dir.z = cos(radians(rot.x)) * cos(radians(rot.y));
	return (dir);
}

uint pack_color(t_color *c)
{
	uchar3 t;

	t.x = clamp(c->x, 0.0f, 1.0f) * 255;
	t.y = clamp(c->y, 0.0f, 1.0f) * 255;
	t.z = clamp(c->z, 0.0f, 1.0f) * 255;
	return ((((t.x << 8u) + t.y) << 8u) + t.z);
}

t_vec3 reflect(t_vec3 vec, t_vec3 normal)
{
	return (vec - 2 * dot(vec, normal) * normal);
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
	t_int		obj_index;
	t_hit		camera_hit;
	t_ray		shadow_ray;
	t_hit		shadow_hit;
	t_color		color;
	t_color		normal_color;
	t_color		depth_color;
	t_vec3		ref;
	t_vec3		light_dir;

	normal_color = COLOR(0,0,0,1);
	depth_color = COLOR(0,0,0,1);
	int id = get_global_id(0);
	camera_ray = new_camera_ray(&options, &camera,
			(uint2){id % options.width, id / options.height});
	obj_index = intersect(objects, options.obj_count, &camera_ray, &camera_hit);
	if (obj_index != -1)
	{
		depth_color = distance(camera_hit.p, VEC(camera.mtx.sC,
											 camera.mtx.sD,
											 camera.mtx.sE)) / 50.0f;
		normal_color = ((camera_hit.n * -1) + 1) / 2;
		t_uint i = 0;
		color = VEC(0,0,0);
		t_vec3 diffuse = VEC(0,0,0);
		t_real specular = 0;
		while (i < options.light_count)
		{
			if (lights[i].id == ID_DIRECT || lights[i].id == ID_POINT)
			{
				if (lights[i].id == ID_DIRECT)
					light_dir = dir_from_rot(lights[i].rot);
				else
					light_dir = normalize(camera_hit.p - lights[i].pos);
				shadow_ray.o = camera_hit.p + camera_hit.n * 0.001f;
				shadow_ray.d = -light_dir;
				if (!(intersect(objects, options.obj_count, &shadow_ray, &shadow_hit) != -1))
				{
					ref = reflect(light_dir, camera_hit.n);
					specular += lights[i].intensity * pow(max(0.f, dot(ref, -camera_ray.d)), 50);
					diffuse += camera_hit.obj->mat.diffuse * lights[i].intensity *
							lights[i].color * max(0.f, dot(camera_hit.n, shadow_ray.d));
				}
			}
			else if (lights[i].id == ID_AMB)
				diffuse += camera_hit.obj->mat.diffuse * lights[i].intensity * lights[i].color;
			i++;
		}
		color = diffuse * 1.5f + specular * 0.1f;
	}
    else
		color = options.background_color;

    index_buffer[id] = obj_index;
	normal_buffer[id] = pack_color(&normal_color);
	depth_buffer[id] = pack_color(&depth_color);
	color_buffer[id] = pack_color(&color);
}

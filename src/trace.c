#include "trace.h"

/*
** Check that distance from origin to new hit is smaller than old
** and update old with new in that case
*/
static inline void update_ray(t_hit *old, t_hit *new, t_ray *ray, int *set)
{
	t_vec3	t;

	if (!*set)
	{
		*old = *new;
		*set = 1;
	}
	else if (v3_mag(v3_sub(&new->at, &ray->orig, &t)) <
		v3_mag(v3_sub(&old->at, &ray->orig, &t)))
		*old = *new;
}

/*
** For each object perform intersection and if intersects set hit
** for the first time, later on hit choose which is closest
** and update hit if new one is closest
*/
t_hit	*inter(t_obj *scene, size_t size, t_ray *ray, t_hit *hit)
{
	t_hit	t;
	t_hit	*new;
	int		set;

	set = 0;
	while (size--)
	{
		new = NULL;
		if (IS_SPH(&scene[size]))
			new = sphere_inter(&scene[size], ray, &t);
		else if (IS_PLN(&scene[size]))
			new = plane_inter(&scene[size], ray, &t);
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

t_hit *sphere_inter(t_obj *obj, t_ray *ray, t_hit *hit)
{
	t_vec3 L;
	t_real tca;
	t_real thc;
	t_real t0;
	t_real t1;

	v3_sub(&obj->pos, &ray->orig, &L);
	tca = v3_dot(&L, &ray->dir);
	if (tca < 0)
		return (NULL);
	thc = v3_dot(&L, &L) - tca * tca;
	if (thc > obj->r)
		return (NULL);
	t0 = R_SQRT(obj->r - thc);
	t1 = tca + t0;
	t0 = tca - t0;
	if (t1 < 0 && t0 < 0)
		return (NULL);
	t0 = t0 > t1 && t1 > 0 ? t1 : t0;

	v3_add(&ray->orig, v3_mull_s(&ray->dir, t0, &L), &hit->at);
	v3_norm(v3_sub(&hit->at, &obj->pos, &L), &hit->norm);
	hit->obj = obj;
	return (hit);
}

t_hit *plane_inter(t_obj *obj, t_ray *ray, t_hit *hit)
{
	t_real d;
	t_vec3 v;
	t_real t;

	d = v3_dot(&ray->dir, &obj->rot);
	if (d < EPSILON)
		return (NULL);
	v3_sub(&ray->orig, &obj->pos, &v);
	t = v3_dot(&v, &ray->dir) / d;
	if (t < 0)
		return (NULL);

	v3_add(&ray->orig, v3_mull_s(&ray->dir, t, &v), &hit->at);
	v3_norm(v3_sub(&hit->at, &obj->pos, &v), &hit->norm);
	hit->obj = obj;
	return (hit);
}

t_hit *cube_inter(t_obj *obj, t_ray *ray, t_hit *hit)
{
	return (NULL);
}

t_hit *cone_inter(t_obj *obj, t_ray *ray, t_hit *hit)
{
	return (NULL);
}

t_hit *cylinder_inter(t_obj *obj, t_ray *ray, t_hit *hit)
{
	return (NULL);
}

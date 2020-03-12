#include "rt.hcl"

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

static inline t_hit *plane_inter(__global t_obj *obj, t_ray *ray, t_hit *hit)
{
    t_real d;
    t_vec3 v;
    t_real t;
    t_vec3 n;

    n = dir_from_rot(obj->rot);
	d = dot(n, ray->dir);
	if (d >= 0)
		return (NULL);
	t = dot(obj->pos - ray->orig, n) / d;
    if (t < 0)
        return (NULL);

	hit->pos = ray->orig + ray->dir * t;
//	if (distance(obj->pos, hit->pos) > 10)
//		return NULL;
	hit->norm = dir_from_rot(obj->rot);
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

static inline t_hit *cylinder_inter(__global t_obj *obj, t_ray *ray, t_hit *hit)
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
    while (size--)
    {
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

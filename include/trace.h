# ifndef TRACE_H

# include "m3d.h"
# include "obj.h"
/*
typedef	struct	s_ray {
	t_vec3	orig;
	t_vec3	dir;
	t_real	t;
}				t_ray;*/

typedef struct	s_hit {
	t_vec3	at;
	t_vec3	norm;
	t_obj	*obj;
}				t_hit;

/*
** Returns hit on objects
** @scene: array of scene objects
** @size: scene objects count
** @ray: ray to shoot
*/
t_hit		*inter(t_obj *scene, size_t size, t_ray *ray, t_hit *hit);

/*
** Per object intersection
** @obj: object
** @ray: ray to shoot
*/
t_hit		*sphere_inter(t_obj *obj, t_ray *ray, t_hit *hit);
t_hit		*plane_inter(t_obj *obj, t_ray *ray, t_hit *hit);
t_hit		*cube_inter(t_obj *obj, t_ray *ray, t_hit *hit);
t_hit		*cone_inter(t_obj *obj, t_ray *ray, t_hit *hit);
t_hit		*cylinder_inter(t_obj *obj, t_ray *ray, t_hit *hit);


# define TRACE_H

# endif

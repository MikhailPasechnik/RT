# ifndef OBJ_HCL
# define OBJ_HCL

# define __OPENCL_DEVICE__
/*
** Include host OpenCL compatible structs
*/
# include "obj.h"
# define EPSILON 1e-6
# ifndef NULL
# define NULL ((void *)0)
# endif
# define VEC(x, y, z)((t_vec3){x, y, z})

typedef struct	s_hit {
	t_vec3	pos;
	t_vec3	norm;
	__global t_obj	*obj;
}				t_hit;

/*
** For each object perform intersection and if intersects set hit
** for the first time, later on hit choose which is closest
** and update hit if new one is closest
*/
t_int			intersect(__global t_obj *scene, size_t size, t_ray *ray, t_hit *hit);
void			print_render_args(t_options *options, t_cam* camera, __global t_obj* scene, __global t_light* lights);
t_mat4			m4_mul(t_mat4 *m, t_mat4 *n);
void			m4_set_rotation(t_mat4 *m, t_vec3 *r);
void			m4_set_translate(t_mat4 *m, t_vec3 *t);
void			m4_identity(t_mat4 *m);
t_vec3			m4_mul_vec3(t_mat4 *m, t_vec3 *v);
t_real			deg2rad(t_real deg);
t_ray			new_camera_ray(t_options *options, t_cam *cam, uint2 pixel);
uint			pack_color(t_color *c);
t_vec3			dir_from_rot(t_vec3 rot);
# endif

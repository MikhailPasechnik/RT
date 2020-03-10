# ifndef OBJ_HCL
# define OBJ_HCL


typedef double cl_double;
typedef double16 cl_double16;
typedef double3 cl_double3;
typedef int cl_int;
typedef uint cl_uint;

# define EPSILON 0.000001
# define VEC(x, y, z)((t_vec3){x, y, z})

/*
** Include host OpenCL compatible structs
**
** Recommend declaring your structure from the widest types first
** down to the narrowest types.
** First, this avoids wasted unused spaces due to alignment.
** Second, this often avoids any headaches
** with different alignments on different devices.
*/
# include "obj.h"

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
t_hit	        *intersect(__global t_obj *scene, size_t size, t_ray *ray, t_hit *hit);
void            print_render_args(t_options *options, t_cam* camera, __global t_obj* scene, __global t_light* lights);
t_mat4          m4_mul(t_mat4 *m, t_mat4 *n);
void            m4_set_rotation(t_mat4 *m, t_vec3 *r);
void            m4_set_translate(t_mat4 *m, t_vec3 *t);
void            m4_identity(t_mat4 *m);
t_vec3          m4_mul_vec3(t_mat4 *m, t_vec3 *v);
t_real          deg2rad(t_real deg);
# endif
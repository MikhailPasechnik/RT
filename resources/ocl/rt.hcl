# ifndef OBJ_HCL
# define OBJ_HCL

# define __OPENCL_DEVICE__
/*
** Include host OpenCL compatible structs
*/
typedef float		t_real;
typedef float16		t_mat4;
typedef float3		t_vec3;
typedef int			t_int;
typedef uint		t_uint;
typedef float3		t_color;
# include "obj.h"
# define EPSILON 1e-16
# ifndef NULL
# define NULL ((void *)0)
# endif
# define VEC(x, y, z)((t_vec3){x, y, z})
# define COLOR(r, g, b, a) ((t_color){r, g, b})
# define CUB(vec, a)((t_vec4){{vec, a}})

# define MAX_BOUNCE 50

typedef struct	s_hit {
	t_vec3	p;
	t_vec3	n;
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
void			m4_set_rotation(t_mat4 *m, t_vec3 r);
void			m4_set_translate(t_mat4 *m, t_vec3 t);
void			m4_identity(t_mat4 *m);
t_vec3			m4_mul_vec3(t_mat4 *m, t_vec3 *v);
t_real			deg2rad(t_real deg);
t_ray			new_camera_ray(t_options *options, t_cam *cam, uint2 pixel);
uint			pack_color(t_color *c);
t_vec3			dir_from_rot(t_vec3 rot);
t_vec3			cam_view_vec3(t_mat4 *m, t_vec3 *v);
t_mat4			m4_transpose(t_mat4 m);
t_vec3			reflect(t_vec3 vec, t_vec3 normal);
t_color			calc_color(t_options options, __global t_obj* objects, __global t_light* lights, int id, t_hit camera_hit, t_ray camera_ray, t_color color);
t_color			coef_color(t_color color, t_real coef);
float3			random_dir(uint bounce, t_options options, float3 normal);
t_color 		pathtracing(int id,
					t_options options,
					__global t_obj* objects,
					__global t_light* lights,
					t_hit camera_hit,
					t_cam camera);
t_color 		trace_one_path(t_options options, __global t_obj* objects, __global t_light* lights, t_ray camera_ray, t_hit camera_hit);
float3			random_dir(uint bounce, t_options options, float3 normal);
float3			rotation_random_dir(float3 normal, float3 random_dir);
float			random_number(t_options options, uint count);

/*
** *********************************** **
** *********************************** **
**             3D vector  			   **
** *********************************** **
** *********************************** **
*/

typedef struct		s_mat3
{
	float3			a;
	float3			b;
	float3			c;
}					t_mat3;

typedef struct		s_gi
{
	t_color			mat_color;
	t_vec3			light_dir;
	t_vec3			normal;
	t_color			emmitance;
	t_color			brdf;
}					t_gi;

float3			v3_cross(float3 a, float3 b);
t_vec3 			v3_mult_matrix(t_mat3 rot_matrix, t_vec3 v);
float			v3_dot_product(t_vec3 v1, t_vec3 v2);
t_vec3			v3_mult_vec_const(t_vec3 v, float n);
t_color			v3_division_vec_on_const(t_color v, float n);
t_mat3			create_rot_matrix(float3 normal);
float3 			random_dir_v20(uint bounce, t_options options, float3 normal);

# endif

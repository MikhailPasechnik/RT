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

typedef struct	s_hit {
	t_vec3			p;
	t_vec3			n;
	t_color 		diff;
	t_real			specular;
	t_real			reflection;
	float2			uv;
	__global t_obj	*obj;
}				t_hit;

/*
** For each object perform intersection and if intersects set hit
** for the first time, later on hit choose which is closest
** and update hit if new one is closest
*/
t_int			intersect(__global t_obj *scene, size_t size, t_ray *ray, t_hit *hit,
				  __global uchar* tx_b, __global t_tx_info* txi_b);
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
t_color			calc_color(t_options options, __global t_obj* objects, __global t_light* lights,
					int id, t_hit camera_hit, t_ray camera_ray, t_color color,
					__global uchar* tx_b, __global t_tx_info* txi_b);
t_color			coef_color(t_color color, t_real coef);
t_color			sample_texture(float2 uv, __global uchar* tx_b, t_tx_info tx_info);
t_color			sepia_effect(t_color color);
# endif

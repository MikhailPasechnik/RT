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


#define DEPTH 6
#define PROBABILITY (1 / (2 * M_PI))
#define BLACK (t_color){0, 0, 0}

/*
** *********************************** **
** *********************************** **
**             STRUCTURES  			   **
** *********************************** **
** *********************************** **
*/

typedef struct		s_hit
{
	t_vec3			p;
	t_vec3			n;
	__global t_obj	*obj;
}					t_hit;

typedef struct		s_colors
{
	t_color			color;
	t_color			normal_color;
	t_color			depth_color;
}					t_colors;

typedef struct		s_mat3
{
	float3			a;
	float3			b;
	float3			c;
}					t_mat3;

typedef struct		s_pathtrace
{
	t_color			emittance;
	float			cos_theta;
	t_color			BRDF;
	t_color			incoming;
}					t_pathtrace;

/*
** *********************************** **
** *********************************** **
**             PROTOTYPES  			   **
** *********************************** **
** *********************************** **
*/

/*
** For each object perform intersection and if intersects set hit
** for the first time, later on hit choose which is closest
** and update hit if new one is closest
*/

/*
** *********************************** **
** *********************************** **
**          general functions  		   **
** *********************************** **
** *********************************** **
*/

t_int			intersect(__global t_obj *scene, size_t size, t_ray *ray, t_hit *hit);
void			print_render_args(t_options *options, t_cam* camera, __global t_obj* scene, __global t_light* lights);
t_ray			new_camera_ray(t_options *options, t_cam *cam, uint2 pixel);
uint			pack_color(t_color *c);
t_vec3			dir_from_rot(t_vec3 rot);
t_vec3			cam_view_vec3(t_mat4 *m, t_vec3 *v);
t_vec3			reflect(t_vec3 vec, t_vec3 normal);
void			fill_buffers(int id,
								t_int obj_index,
								t_color normal_color,
								t_color depth_color,
								t_color color,
								__global t_int* color_buffer,
								__global t_int* index_buffer,
								__global t_int* normal_buffer,
								__global t_int* depth_buffer);
t_int			trace(	int id,
						t_options options,
						__global t_obj* objects,
						__global t_light* lights,
						t_ray *camera_ray,
						t_cam camera,
						t_hit *camera_hit,
						t_color *c);
t_real			deg2rad(t_real deg);
int				compare_color(t_color col_1, t_color col_2);

/*
** *********************************** **
** *********************************** **
**             4D vector  			   **
** *********************************** **
** *********************************** **
*/

t_mat4			m4_mul(t_mat4 *m, t_mat4 *n);
void			m4_set_rotation(t_mat4 *m, t_vec3 r);
void			m4_set_translate(t_mat4 *m, t_vec3 t);
void			m4_identity(t_mat4 *m);
t_vec3			m4_mul_vec3(t_mat4 *m, t_vec3 *v);
t_mat4			m4_transpose(t_mat4 m);

/*
** *********************************** **
** *********************************** **
**             3D vector  			   **
** *********************************** **
** *********************************** **
*/

t_vec3			v3_cross(t_vec3 a, t_vec3 b);
t_vec3 			v3_mult_matrix(t_mat3 rot_matrix, t_vec3 v);
float			v3_dot_product(t_vec3 v1, t_vec3 v2);
t_vec3			v3_mult_vec_const(t_vec3 v, float n);
t_vec3			v3_division_vec_on_const(t_vec3 v, float n);

/*
** *********************************** **
** *********************************** **
**             pathracing  			   **
** *********************************** **
** *********************************** **
*/

float3			random_dir(uint bounce, t_options options, float3 normal);
float			random_number(t_options options, uint count);
t_mat3			create_rot_matrix(float3 normal);
float3			rotation_random_dir(float3 normal, float3 random_dir);
t_color	 		trace_one_path(int id,
								t_options options,
								__global t_obj* objects,
								__global t_light* lights,
								t_ray *camera_ray,
								t_cam camera,
								t_hit *camera_hit,
								t_color *c,
								int depth,
								int *obj_index,
								t_pathtrace *b);
// t_color 		pathtracing(int id,
// 							t_options options,
// 							__global t_obj* objects,
// 							__global t_light* lights,
// 							t_ray *camera_ray,
// 							t_cam camera,
// 							int obj_index);

# endif

// void RenderPixel(uint x, uint y, UniformSampler *sampler) {
//     Ray ray = m_scene->Camera->CalculateRayFromPixel(x, y, sampler);

//     float3 color(0.0f);
//     float3 throughput(1.0f);
//     SurfaceInteraction interaction;

//     // Bounce the ray around the scene
//     const uint maxBounces = 15;
//     for (uint bounces = 0; bounces < maxBounces; ++bounces) {
//         m_scene->Intersect(ray);

//         // The ray missed. Return the background color
//         if (ray.GeomID == INVALID_GEOMETRY_ID) {
//             color += throughput * m_scene->BackgroundColor;
//             break;
//         }

//         // Fetch the material
//         Material *material = m_scene->GetMaterial(ray.GeomID);
//         // The object might be emissive. If so, it will have a corresponding light
//         // Otherwise, GetLight will return nullptr
//         Light *light = m_scene->GetLight(ray.GeomID);

//         // If we hit a light, add the emission
//         if (light != nullptr) {
//             color += throughput * light->Le();
//         }

//         interaction.Position = ray.Origin + ray.Direction * ray.TFar;
//         interaction.Normal = normalize(m_scene->InterpolateNormal(ray.GeomID, ray.PrimID, ray.U, ray.V));
//         interaction.OutputDirection = normalize(-ray.Direction);


//         // Get the new ray direction
//         // Choose the direction based on the bsdf        
//         material->bsdf->Sample(interaction, sampler);
//         float pdf = material->bsdf->Pdf(interaction);

//         // Accumulate the weight
//         throughput = throughput * material->bsdf->Eval(interaction) / pdf;

//         // Shoot a new ray

//         // Set the origin at the intersection point
//         ray.Origin = interaction.Position;

//         // Reset the other ray properties
//         ray.Direction = interaction.InputDirection;
//         ray.TNear = 0.001f;
//         ray.TFar = infinity;


//         // Russian Roulette
//         if (bounces > 3) {
//             float p = std::max(throughput.x, std::max(throughput.y, throughput.z));
//             if (sampler->NextFloat() > p) {
//                 break;
//             }

//             throughput *= 1 / p;
//         }
//     }

//     m_scene->Camera->FrameBufferData.SplatPixel(x, y, color);
// }




typedef struct	s_object
{
	double3 p;
	double	p1;
	double	p2;
	double	p3;
}				t_object;
typedef struct	s_inter
{
	double3 p;
	int 	id;
}				t_inter;
typedef struct f {
    float3 f16;
    float3 f17;
    float  f18
}				f;
typedef float		t_real;
typedef float16		t_mat4;
typedef float3		t_vec3;
typedef int			t_int;
typedef uint		t_uint;
typedef float3		t_color;

typedef struct			s_cam_
{
	t_vec3				pos;
	t_vec3				dir;
	t_real				fov;
}						t_cam_;

__kernel void k_render(
		uint width,
		uint height,
		__global t_object* scene,
		__global char* output,
		t_cam_ f16
		)
{
	int x = get_global_id(0);
	int y = get_global_id(1);
	int i = y * width + x;
	output[i] = '#';
}


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

__kernel void k_render(
		uint width,
		uint height,
		__global t_object* scene,
		__global char* output)
{
	int x = get_global_id(0);
	int y = get_global_id(1);
	int i = y * width + x;
	output[i] = '#';
}
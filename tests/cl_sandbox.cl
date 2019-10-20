
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
		__global t_object* scene,
		__global t_inter* inter)
{
	int id = get_global_id(0);
	inter[0].p.x = 22;
	inter[0].p.y = 33;
	inter[0].p.z = 44;
	inter[0].id = 21;
	printf("CL: id: %d\n", id);
}

#include <assert.h>
#include "rt.h"


typedef struct	s_object
{
	cl_double3 p;
	cl_double	p1;
	cl_double	p2;
	cl_double	p3;
}				t_object;

typedef struct	s_inter
{
	cl_double3 p;
	cl_int 	id;
}				t_inter;


int main(void)
{
	int			err;
	t_ocl		ocl;
	t_renderer	ren;
	cl_kernel   k;

	t_object   	scene;
	cl_mem 		scene_mem;
	t_inter		inter;
	cl_mem 		inter_mem;

	scene.p = (cl_double3){1, 2, 3};
	assert(ocl_init(&ocl));
	assert(new_renderer(&ren, &ocl, "tests/cl_sandbox.cl", NULL));
	k = clCreateKernel(ren.program, "k_render", &err);
	assert(!OCL_ERROR2(err));

	// Scene
	scene_mem = clCreateBuffer(ocl.context, CL_MEM_READ_ONLY, sizeof(t_object), &scene, &err);
	assert(!OCL_ERROR2(err));
	err |= clEnqueueWriteBuffer(ren.queue, scene_mem, CL_TRUE, 0, sizeof(t_object),
			&scene, 0, NULL, NULL);

	// Intersection
	inter_mem = clCreateBuffer(ocl.context, CL_MEM_WRITE_ONLY, sizeof(t_inter), NULL, &err);
	assert(!OCL_ERROR2(err));
	err |= clSetKernelArg(k, 0, sizeof(scene_mem), &scene_mem);
	err |= clSetKernelArg(k, 1, sizeof(scene_mem), &inter_mem);
	assert(!OCL_ERROR2(err));

	// Do it
	size_t size = 1;
	err = clEnqueueNDRangeKernel(ren.queue, k, 1, NULL, &size, NULL, 0, NULL, NULL);
	assert(!OCL_ERROR2(err));
	assert(!OCL_ERROR2(clFinish(ren.queue)));
	assert(!OCL_ERROR2(
			clEnqueueReadBuffer(
					ren.queue, inter_mem, CL_TRUE, 0,
					sizeof(t_inter), &inter, 0, NULL, NULL
	)));
	ft_printf("Intersection: %d [%lf %lf %lf]\n", inter.id, inter.p.x, inter.p.y, inter.p.z);
	return (0);
}

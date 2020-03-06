#include <assert.h>
#include "rt.h"

typedef cl_int t_int;

typedef struct 			s_mat_
{
	t_vec3			diffuse;
	t_real			specular;
}	t_mat_;

typedef struct s_obj_
{
	t_mat_				mat;
	t_vec3				pos;
	t_vec3				rot;
	t_real				h;
	t_real				r;
}		t_obj_;

void fake_sphere(t_obj_ *s)
{
	s->pos = VEC(1, 3333333, 3);
	s->rot = VEC(3, 2, 1);
//	s->i = (cl_int3){4, 4, 4};
	s->r = 2;
	s->h = 44;
	s->mat.specular = 44;
	s->mat.diffuse = VEC(1, 3333333, 3);
}

int main(void)
{
	int			err;
	t_ocl		ocl;
	t_renderer	ren;
	cl_kernel   k;

	int		w = 20;
	int		h = 20;
	int		s = 4;
	t_obj_   	*scene = malloc(sizeof(t_obj_) * s);
	cl_mem 		scene_mem;
	cl_mem 		output_mem;
	cl_char		output[160000];
	ft_memset(output, '.', w * h + sizeof(cl_char));
	output[w * h] = '\0';

	int i = 0;
	while (i < s)
	{
		fake_sphere(&scene[i++]);
	}
	printf("\n");
	assert(ocl_init(&ocl));
	assert(new_renderer(&ren, &ocl, "C:\\Users\\mpasechnik\\RTv1\\tests1\\cl_sandbox.cl", NULL));
	k = clCreateKernel(ren.program, "k_render", &err);
	assert(!OCL_ERROR2(err));

	// Scene
	scene_mem = clCreateBuffer(ocl.context, CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR, s * sizeof(t_obj_), scene, &err);
	assert(!OCL_ERROR2(err));
//	err = clEnqueueWriteBuffer(ren.queue, scene_mem, CL_TRUE, 0, s * sizeof(t_obj_), scene, 0, NULL, NULL);
//	assert(!OCL_ERROR2(err));

	t_vec3 test_vec[10] = {0};
	test_vec[5] = VEC(666666666666, 4, 5);
	cl_mem test_mem = clCreateBuffer(ocl.context, CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR, 10 * sizeof(t_vec3), test_vec, &err);
	assert(!OCL_ERROR2(err));
	printf("scene_mem: %d scene: %d\n", sizeof(scene_mem), s * sizeof(t_obj_));

	assert(!OCL_ERROR2(err));
	// Set arguments
	output_mem = clCreateBuffer(ocl.context, CL_MEM_WRITE_ONLY, sizeof(cl_char) * w * h, NULL, &err);
	assert(!OCL_ERROR2(err));
	err |= clSetKernelArg(k, 0, sizeof(cl_uint), &w);
	err |= clSetKernelArg(k, 1, sizeof(cl_uint), &h);
	err |= clSetKernelArg(k, 2, sizeof(cl_uint), &s);
	err |= clSetKernelArg(k, 3, sizeof(scene_mem), &scene_mem);
	err |= clSetKernelArg(k, 4, sizeof(test_mem), &test_mem);
	err |= clSetKernelArg(k, 5, sizeof(output_mem), &output_mem);
	assert(!OCL_ERROR2(err));

	int size = w * h;
	err = clEnqueueNDRangeKernel(ren.queue, k, 1, NULL, &size, NULL, 0, NULL, NULL);
	assert(!OCL_ERROR2(err));
	assert(!OCL_ERROR2(clFinish(ren.queue)));
	clEnqueueReadBuffer(ren.queue, output_mem, CL_TRUE, 0,
						sizeof(cl_int) * size, &output, 0, NULL, NULL
	);
	assert(!OCL_ERROR2(err));
	printf("%s", output);
	return (0);
}

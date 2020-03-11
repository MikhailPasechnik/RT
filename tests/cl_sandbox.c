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

	cl_uint		w = 20;
	cl_uint		h = 20;
	t_object   	scene;
	cl_mem 		scene_mem;
	cl_mem 		output_mem;
	cl_char		output[w * h + sizeof(cl_char)];
	ft_memset(output, '.', w * h + sizeof(cl_char));
	output[w * h] = '\0';

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
	output_mem = clCreateBuffer(ocl.context, CL_MEM_WRITE_ONLY, sizeof(cl_char) * w * h, NULL, &err);
	assert(!OCL_ERROR2(err));
	err |= clSetKernelArg(k, 0, sizeof(cl_uint), &w);
	err |= clSetKernelArg(k, 1, sizeof(cl_uint), &h);
	err |= clSetKernelArg(k, 2, sizeof(scene_mem), &scene_mem);
	err |= clSetKernelArg(k, 3, sizeof(output_mem), &output_mem);
	assert(!OCL_ERROR2(err));

	// Do it
	t_urect r;
	r = (t_urect){10, 10, 5, 5};
	size_t buffer_offset[3] = {r.orig[0], r.orig[1], 0};
	size_t host_offset[3] = {r.orig[0], r.orig[1], 0};
	size_t region[3] = {r.size[0], r.size[1], 1};
	size_t  buffer_row_pitch = w;
	size_t  buffer_slice_pitch = 0;
	err = clEnqueueNDRangeKernel(ren.queue, k, 2, &r.orig, &r.size, NULL, 0, NULL, NULL);
	assert(!OCL_ERROR2(err));
	assert(!OCL_ERROR2(clFinish(ren.queue)));
	err = clEnqueueReadBufferRect(
			ren.queue,
			output_mem,
			CL_TRUE,
			buffer_offset,
			host_offset,
			region,

			buffer_row_pitch,
			buffer_slice_pitch,
			buffer_row_pitch,
			buffer_slice_pitch,

			&output,
			0, NULL, NULL
	);
	assert(!OCL_ERROR2(err));

	int x, y;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			ft_printf("%c", output[y * w + x]);
			x++;
		}
		ft_printf("\n");
		y++;
	}
	return (0);
}

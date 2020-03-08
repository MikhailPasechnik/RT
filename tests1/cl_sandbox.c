#include <assert.h>
#include "rt.h"
#include "obj.h"

typedef cl_int t_int;

void print_m4(t_mat4 M)
{
    printf("[%.3f %.3f %.3f %.3f\n"
           " %.3f %.3f %.3f %.3f\n"
           " %.3f %.3f %.3f %.3f\n"
           " %.3f %.3f %.3f %.3f]\n",
           M.s0, M.s1, M.s2, M.s3,
           M.s4, M.s5, M.s6, M.s7,
           M.s8, M.s9, M.sA, M.sB,
           M.sC, M.sD, M.sE, M.sF
       );
}
t_mat4 m4_mul2(t_mat4 M, t_mat4 N)
{
    t_mat4 result = (t_mat4){
            M.s0 * N.s0 + M.s1 * N.s4 + M.s2 * N.s8 + M.s3 * N.sC,
            M.s0 * N.s1 + M.s1 * N.s5 + M.s2 * N.s9 + M.s3 * N.sD,
            M.s0 * N.s2 + M.s1 * N.s6 + M.s2 * N.sA + M.s3 * N.sE,
            M.s0 * N.s3 + M.s1 * N.s7 + M.s2 * N.sB + M.s3 * N.sF,
            M.s4 * N.s0 + M.s5 * N.s4 + M.s6 * N.s8 + M.s7 * N.sC,
            M.s4 * N.s1 + M.s5 * N.s5 + M.s6 * N.s9 + M.s7 * N.sD,
            M.s4 * N.s2 + M.s5 * N.s6 + M.s6 * N.sA + M.s7 * N.sE,
            M.s4 * N.s3 + M.s5 * N.s7 + M.s6 * N.sB + M.s7 * N.sF,
            M.s8 * N.s0 + M.s9 * N.s4 + M.sA * N.s8 + M.sB * N.sC,
            M.s8 * N.s1 + M.s9 * N.s5 + M.sA * N.s9 + M.sB * N.sD,
            M.s8 * N.s2 + M.s9 * N.s6 + M.sA * N.sA + M.sB * N.sE,
            M.s8 * N.s3 + M.s9 * N.s7 + M.sA * N.sB + M.sB * N.sF,
            M.sC * N.s0 + M.sD * N.s4 + M.sE * N.s8 + M.sF * N.sC,
            M.sC * N.s1 + M.sD * N.s5 + M.sE * N.s9 + M.sF * N.sD,
            M.sC * N.s2 + M.sD * N.s6 + M.sE * N.sA + M.sF * N.sE,
            M.sC * N.s3 + M.sD * N.s7 + M.sE * N.sB + M.sF * N.sF};
    return (result);
}

int rand_interval(int min, int max)
{
    return  (rand() % (max - min + 1)) + min;
}

void fake_obj(t_obj *s, t_int id)
{
	s->pos = VEC(
	        rand_interval(-10, 10),
	        rand_interval(-10, 10),
	        rand_interval(7, 25)
    );
	s->rot = VEC(1,0,0);
	s->radius = rand_interval(1, 5);
	s->height = rand_interval(1, 5);
	s->id = id;
	s->symbol = rand_interval(49, 100);
	s->mat.ior = rand_interval(0, 255) / 255.0;
	s->mat.fresnel = rand_interval(0, 255) / 255.0;
	s->mat.reflection = rand_interval(0, 255) / 255.0;
	s->mat.refraction = rand_interval(0, 255) / 255.0;
	s->mat.specular = rand_interval(0, 255) / 255.0;
	s->mat.diffuse = VEC(
	        rand_interval(0, 255),
	        rand_interval(0, 255),
	        rand_interval(0, 255)
    );
    v3_mull_s(&s->mat.diffuse, 1 / 255.0, &s->mat.diffuse);
}

void ground_plane(t_obj *o)
{
    o->id = ID_PLN;
    o->symbol = '`';
    o->rot = VEC(0, 0, -1);
    o->rot = VEC(0, 1, 0);
}

int main(void)
{
	int			err;
	t_ocl		ocl;
	t_renderer	ren;
	cl_kernel   k;

	int		w = 100*1.6;
	int		h = 100*1.6;
	int		fow = 68;
	int		s = 55;
	t_obj   	scene[s];
	cl_mem 		scene_mem;
	cl_mem 		output_mem;
    t_int		output[w * h + sizeof(t_int)];
	ft_memset(output, '.', w * h + sizeof(t_int));
	output[w * h] = '\0';

	int i = 0;
	while (i < s)
	{
        fake_obj(&scene[i++], ID_SPH);
	}
    ground_plane(&scene[0]);
    v3_norm(&scene[0].rot, &scene[0].rot);
	assert(ocl_init(&ocl));
	assert(new_renderer(&ren, &ocl, RT_CL_SRC, RT_CL_INCLUDE));
	k = clCreateKernel(ren.program, RT_K_RENDER, &err);
	assert(!OCL_ERROR2(err));

	// Scene
	scene_mem = clCreateBuffer(ocl.context, CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR, s * sizeof
	(t_obj), scene, &err);
	assert(!OCL_ERROR2(err));
//	err = clEnqueueWriteBuffer(ren.queue, scene_mem, CL_TRUE, 0, s * sizeof(t_obj), scene, 0, NULL, NULL);
//	assert(!OCL_ERROR2(err));

	t_vec3 test_vec[10] = {0};
	test_vec[5] = VEC(4, 4, 5);
	assert(!OCL_ERROR2(err));
    cl_mem lights_mem = clCreateBuffer(ocl.context, CL_MEM_READ_ONLY, 1, test_vec, &err);
	assert(!OCL_ERROR2(err));
	// Set arguments
	output_mem = clCreateBuffer(ocl.context, CL_MEM_READ_WRITE, sizeof(t_int) * w * h, NULL, &err);
	assert(!OCL_ERROR2(err));
	t_options options = (t_options){
	    .background_color = VEC(0,0,0),
	    .reflection_depth = 0,
        .width = w,
        .height = h,
        .obj_count = s,
        .light_count = 0,
	};

	t_cam cam = {
        .fov=fow,
        .pos = VEC(0,0,0),
        .dir = VEC(0,0,1)
	};
	err |= clSetKernelArg(k, 1, sizeof(t_options), &options);
	err |= clSetKernelArg(k, 2, sizeof(t_cam), &cam);
	err |= clSetKernelArg(k, 3, sizeof(cl_mem), &scene_mem);
	err |= clSetKernelArg(k, 4, sizeof(cl_mem), &lights_mem);
	err |= clSetKernelArg(k, 0, sizeof(cl_mem), &output_mem);
	assert(!OCL_ERROR2(err));

	int size = w * h;
	int offset = 0;
	err = clEnqueueNDRangeKernel(ren.queue, k, 1, &offset, &size, NULL, 0, NULL, NULL);
	assert(!OCL_ERROR2(err));
	assert(!OCL_ERROR2(clFinish(ren.queue)));
	clEnqueueReadBuffer(ren.queue, output_mem, CL_TRUE, 0,
						sizeof(t_int) * size, &output, 0, NULL, NULL
	);
	assert(!OCL_ERROR2(err));
	printf("dot: %f\n", v3_dot(&VEC(1,2,3), &VEC(1,2,3)));
    int x, y;
    y = 0;
    while (y < h)
    {
        x = 0;
        while (x < w)
        {
            ft_printf(" %c ", (char)output[y * w + x]);
            x++;
        }
        ft_printf("\n");
        y++;
    }
	return (0);
}

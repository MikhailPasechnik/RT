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
	t_real				height;
	t_real				radius;
}		t_obj_;
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

void fake_sphere(t_obj_ *s)
{
	s->pos = VEC(0,0, 2);
	s->rot = VEC(3, 2, 1);
//	s->i = (cl_int3){4, 4, 4};
	s->radius = 10;
	s->height = 0;
	s->mat.specular = 44;
	s->mat.diffuse = VEC(1, 3333333, 3);
}

int main(void)
{
    t_mat4 d161 = (t_mat4){
            1, 2, 0, 0,
            0, 1, 2, 0,
            0, 0, 1, 3,
            0, 0, 0, 1
    };
    t_mat4 d162 = (t_mat4){
            1, 0, 0, 0,
            5, 1, 0, 0,
            0, 4, 1, 0,
            0, 0, 0, 1
    };
    t_mat4 d163;
    m4_mul(&d161, &d162, &d163);
    m4_inv(&d161, &d163);
    print_m4(d163);
    print_m4(m4_mul2(d161,d162));

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
    cl_char		output[w * h + sizeof(cl_char)];
	ft_memset(output, '.', w * h + sizeof(cl_char));
	output[w * h] = '\0';

	int i = 0;
	while (i < s)
	{
		fake_sphere(&scene[i++]);
	}
	printf("\n");
	assert(ocl_init(&ocl));
	assert(new_renderer(&ren, &ocl, "tests1/cl_sandbox.cl", NULL));
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
	output_mem = clCreateBuffer(ocl.context, CL_MEM_READ_WRITE, sizeof(cl_char) * w * h, NULL, &err);
	assert(!OCL_ERROR2(err));
	err |= clSetKernelArg(k, 0, sizeof(cl_uint), &w);
	err |= clSetKernelArg(k, 1, sizeof(cl_uint), &h);
	err |= clSetKernelArg(k, 2, sizeof(cl_uint), &s);
	err |= clSetKernelArg(k, 3, sizeof(cl_mem), &scene_mem);
	err |= clSetKernelArg(k, 4, sizeof(cl_mem), &test_mem);
	err |= clSetKernelArg(k, 5, sizeof(cl_mem), &output_mem);
	assert(!OCL_ERROR2(err));

	int size = w * h;
	int offset = 0;
	err = clEnqueueNDRangeKernel(ren.queue, k, 1, &offset, &size, NULL, 0, NULL, NULL);
	assert(!OCL_ERROR2(err));
	assert(!OCL_ERROR2(clFinish(ren.queue)));
	clEnqueueReadBuffer(ren.queue, output_mem, CL_TRUE, 0,
						sizeof(cl_char) * size, &output, 0, NULL, NULL
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
            ft_printf(" %c ", output[y * w + x]);
            x++;
        }
        ft_printf("\n");
        y++;
    }
	return (0);
}

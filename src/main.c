/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2019/06/21 12:52:38 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->size_x = WIN_X;
	mlx->size_y = WIN_Y;
	mlx->win_ptr = mlx_new_window(
			mlx->mlx_ptr, mlx->size_x, mlx->size_y, WIN_TITLE);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->size_x, mlx->size_y);
	mlx->pic_ptr = (int *)mlx_get_data_addr(
			mlx->img_ptr, &mlx->bpp, &mlx->size_line, &mlx->endian);
	mlx_key_hook(mlx->win_ptr,  &key_press, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, &finish, mlx);
}

void    start()
{
	t_mlx mlx;
	init_mlx(&mlx);
	mlx_loop(mlx.mlx_ptr);
}

#define DATA_SIZE (1024 * 16)

int		main(int argc, char **argv)
{
	if (argc != 1)
	{
		ft_putstr(USG_MSG);
		return (0);
	}
	int err;
	float data[DATA_SIZE];
	float result[DATA_SIZE];
	cl_mem mem_in;
	cl_mem mem_out;
	unsigned int corresc;
	size_t global;
	size_t local;
	unsigned int count = DATA_SIZE;

	int i = 0;
	while (i < DATA_SIZE)
	{
		data[i] = i + 1;
		i++;
	}
//	start();
	t_cl cl;
	opencl_init(&cl, &opencl_simple_notify);
	cl_program program;
	program = opencl_compile_program(cl.context, cl.device, "src/test.cl", 0);
	if (!program)
		printf("Failed opencl_compile_program\n");
	cl_kernel kernel;
	kernel = clCreateKernel(program, "square", &err);
	if (err != CL_SUCCESS)
		printf("Failed clCreateKernel\n");
	mem_in = clCreateBuffer(cl.context, CL_MEM_READ_ONLY, sizeof(*data) * DATA_SIZE, NULL, NULL);
	mem_out = clCreateBuffer(cl.context, CL_MEM_READ_WRITE, sizeof(*result) * DATA_SIZE, NULL, NULL);
	if (!mem_in || !mem_out)
		printf("Failed clCreateBuffer\n");

	err = clEnqueueWriteBuffer(cl.queue, mem_in, CL_TRUE, 0, sizeof(*result) * DATA_SIZE, data, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		printf("Failed clEnqueueWriteBuffer\n");
	err = 0;
	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &mem_in);
	err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &mem_out);
	err |= clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);
	if (err != CL_SUCCESS)
		printf("Failed clSetKernelArg\n");

	err = clGetKernelWorkGroupInfo(kernel, cl.device, CL_KERNEL_WORK_GROUP_SIZE, sizeof(local), &local, NULL);
	if (err != CL_SUCCESS)
		printf("Failed clGetKernelWorkGroupInfo\n");
	printf("local %d\n", (int)local);

	global = count;
	if (local > count)
		local = count;
	err = clEnqueueNDRangeKernel(cl.queue, kernel, 1, NULL, &global, &local, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		printf("Failed clEnqueueNDRangeKernel: %s\n", opencl_get_error_string(err));

	clFinish(cl.queue);
	clEnqueueReadBuffer(cl.queue, mem_out, CL_TRUE, 0, sizeof(*result) * DATA_SIZE, result, 0, NULL, NULL);

	i = count - 5;
	while (i < count)
	{
		printf("%d = %f > %f\n", i, data[i], result[i]);
		i++;
	}

	program ? opencl_log_program_build(program, cl.device) : 0;
	program ? clReleaseProgram(program) : 0;
	opencl_release(&cl);
	return (0);
}

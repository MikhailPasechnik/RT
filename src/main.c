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


#include "SDL.h"
#include "fractol.h"
#include "ocl.h"

#define DATA_SIZE (1024)

int		main(int argc, char **argv)
{

	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
								  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface( window );

			//Fill the surface white
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

			//Update the surface
			SDL_UpdateWindowSurface( window );
		}
	}

	if (argc != 1 || !argv)
	{
		ft_putstr(USG_MSG);
		return (0);
	}
	int err;
	float data[DATA_SIZE];
	float result[DATA_SIZE];
	cl_mem mem_in;
	cl_mem mem_out;
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
	t_ocl cl;
	ocl_init(&cl);
	cl_program program;
	program = ocl_compile_program(cl.context, cl.device, "src/test.cl", 0);
	if (!program)
		printf("Failed ocl_compile_program\n");
	cl_kernel kernel;
	kernel = clCreateKernel(program, "square", &err);
	if (err != CL_SUCCESS)
		OCL_ERROR(err, "Failed clCreateKernel\n");
	mem_in = clCreateBuffer(cl.context, CL_MEM_READ_ONLY, sizeof(*data) * DATA_SIZE, NULL, NULL);
	mem_out = clCreateBuffer(cl.context, CL_MEM_READ_WRITE, sizeof(*result) * DATA_SIZE, NULL, NULL);
	if (!mem_in || !mem_out)
		OCL_ERROR(err, "Failed clCreateBuffer\n");
	err = clEnqueueWriteBuffer(cl.queue, mem_in, CL_TRUE, 0, sizeof(*result) * DATA_SIZE, data, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		OCL_ERROR(err, "Failed clEnqueueWriteBuffer\n");
	err = 0;
	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &mem_in);
	err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &mem_out);
	err |= clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);
	if (err != CL_SUCCESS)
		OCL_ERROR(err, "Failed clSetKernelArg\n");

	err = clGetKernelWorkGroupInfo(kernel, cl.device, CL_KERNEL_WORK_GROUP_SIZE, sizeof(local), &local, NULL);
	if (err != CL_SUCCESS)
		OCL_ERROR(err, "Failed clGetKernelWorkGroupInfo\n");
	printf("local %d\n", (int)local);

	// Number of total work items - localSize must be devisor
	global  = ceil(count/(float)local)*local;
	if (local > count)
		local = count;
	err = clEnqueueNDRangeKernel(cl.queue, kernel, 1, NULL, &global, &local, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		OCL_ERROR(err, "Failed clEnqueueNDRangeKernel");

	clFinish(cl.queue);
	if (OCL_ERROR2(
		clEnqueueReadBuffer(
			cl.queue, mem_out, CL_TRUE, 0,
			sizeof(*result) * DATA_SIZE, result, 0, NULL, NULL
		)
	))
		exit(1);

	i = 0;
	while (i < (int)count)
	{
		printf("%d = %f > %f\n", i, data[i], result[i]);
		i++;
	}
	program ? ocl_log_program_build(program, cl.device) : 0;
	program ? clReleaseProgram(program) : 0;
	ocl_release(&cl);
	//Destroy window
	SDL_Delay( 2000 );

	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();
	return (0);
}

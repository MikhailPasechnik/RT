/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2019/06/21 12:52:38 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	log_build_log(t_renderer *ren, t_ocl *ocl, int fd)
{
	char	*log;

	log = ocl_get_build_log(ren->program, ocl->device);
	if (log)
	{
		ft_putendl_fd(log, fd);
		free(log);
	}
	return (0);
}

int new_renderer(t_renderer *ren, t_ocl *ocl, char *src, char *options)
{
	int			err;

	if (!(ren->src = ft_strsplit_any(src, " \n")))
		return (0);
	ren->src_count = rt_tab_len(ren->src);
	ren->program = ocl_create_program(ocl->context,
			(const char **)ren->src, ren->src_count);
	if (!ren->program || OCL_ERROR(clBuildProgram(
			ren->program, 0, NULL, options, NULL, NULL),
					"Failed to build program"))
		return (log_build_log(ren, ocl, 2));
#ifdef __APPLE__
	ren->queue = clCreateCommandQueue(ocl->context,
			ocl->device, 0, &err);
#else
	ren->queue = clCreateCommandQueueWithProperties(ocl->context,
			ocl->device, 0, &err);
#endif
	ren->render_kernel = clCreateKernel(ren->program, "k_render", &err);
	if (OCL_ERROR(err, "Failed to create queue"))
		return (0);
	return (1);
}

void    delete_renderer(t_renderer *ren)
{
	ren->queue ? clReleaseCommandQueue(ren->queue) : 0;
	ren->program ? clReleaseProgram(ren->program) : 0;
	rt_tab_free(ren->src);
}

static int	pre_render(t_renderer *ren, t_ocl *ocl)
{
	int			err;

	err = 0;
	if (!ren->out_mem || ren->width != ren->out_w || ren->height != ren->out_h)
	{
		ren->out_w = ren->height;
		ren->out_h = ren->width;
		ren->out_mem ? clReleaseMemObject(ren->out_mem) : 0;
		ren->out_mem = clCreateBuffer(ocl->context, CL_MEM_READ_WRITE,
				sizeof(t_int) * ren->out_w * ren->out_h, NULL, &err);
	}
	err |= clSetKernelArg(ren->render_kernel, RT_K_OUTPUT_ARG,
			sizeof(cl_mem), &ren->out_mem);
	return (OCL_ERROR(err, "Failed to pre render!") ? 0 : 1);
}

int			render(t_renderer *ren, t_ocl *ocl, cl_int *result, SDL_Rect *rect)
{
	int		err;
	size_t	size;

	if (!pre_render(ren, ocl))
		return (0);
	size = ren->out_w * ren->out_h;
	err = clEnqueueNDRangeKernel(ren->queue, ren->render_kernel,
			1, NULL, &size, NULL, 0, NULL, NULL);
	if (OCL_ERROR(err, "Failed to enqueue kernel!"))
		return (0);
	if OCL_ERROR(clFinish(ren->queue), "Failed to finish queue!")
		return (0);
	if (OCL_ERROR(clEnqueueReadBuffer(ren->queue, ren->out_mem, CL_TRUE, 0,
			sizeof(cl_int) * size, result, 0, NULL, NULL
			), "Failed to read render output to the surface"))
		return (0);
	return (1);
}

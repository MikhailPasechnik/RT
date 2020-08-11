/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvernius <cvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2020/08/10 20:26:25 by cvernius         ###   ########.fr       */
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

int			new_renderer(t_renderer *ren, t_ocl *ocl, char *src, char *options)
{
	int		err;

	if (!(ren->src = ft_strsplit_any(src, " \n")))
		return (0);
	ren->src_count = rt_tab_len(ren->src);
	ren->program = ocl_create_program(ocl->context,
			(const char **)ren->src, ren->src_count);
	if (!ren->program || OCL_ERROR(clBuildProgram(
			ren->program, 0, NULL, options, NULL, NULL),
					"Failed to build program"))
		return (log_build_log(ren, ocl, 2));
	if (OPENCL_VERSION == 1)
		ren->queue = clCreateCommandQueueWithProperties(ocl->context,
			ocl->device, 0, &err);
	else
		ren->queue = clCreateCommandQueue(ocl->context, ocl->device, 0, &err);
	if (OCL_ERROR(err, "Failed to create queue"))
		return (0);
	ren->render_kernel = clCreateKernel(ren->program, "k_render", &err);
	if (OCL_ERROR(err, "Failed to create render kernel"))
		return (0);
	ren->pproc_kernel = clCreateKernel(ren->program, "k_postprocess", &err);
	if (OCL_ERROR(err, "Failed to create postprocess kernel"))
		return (0);
	return (1);
}

void		delete_renderer(t_renderer *ren)
{
	ren->queue ? clReleaseCommandQueue(ren->queue) : 0;
	ren->program ? clReleaseProgram(ren->program) : 0;
	ren->src ? rt_tab_free(ren->src) : 0;
	free_buffer(&ren->index_buf);
	free_buffer(&ren->light_buf);
	free_buffer(&ren->obj_buf);
	free_buffer(&ren->texture_buf);
	free_buffer(&ren->texture_info_buf);
	free_tx_buffer(&ren->color_buf);
	free_tx_buffer(&ren->color_buf2);
	free_buffer(&ren->normal_buf);
	free_buffer(&ren->depth_buf);
	free_buffer(&ren->seed_buf);
	free_buffer(&ren->mc_buf);
	free_buffer(&ren->uv_buf);
}

static int	pre_render(t_renderer *ren, t_ocl *ocl)
{
	(void)ren;
	(void)ocl;
	return (1);
}

int			render(t_renderer *ren, t_ocl *ocl)
{
	int		err;
	size_t	size;

	if (!pre_render(ren, ocl))
		return (0);
	size = ren->width * ren->height;
	err = clEnqueueNDRangeKernel(
			ren->queue, ren->render_kernel, 1, NULL, &size,
			NULL, 0, NULL, NULL);
	if (OCL_ERROR(err, "Failed to enqueue render kernel!"))
		return (0);
	if (ren->pproc_enabled)
	{
		err = clEnqueueNDRangeKernel(
				ren->queue, ren->pproc_kernel, 1, NULL, &size,
				NULL, 0, NULL, NULL);
		if (OCL_ERROR(err, "Failed to enqueue postprocess kernel!"))
			return (0);
	}
	if (OCL_ERROR(clFinish(ren->queue), "Failed to finish queue!"))
		return (0);
	return (1);
}

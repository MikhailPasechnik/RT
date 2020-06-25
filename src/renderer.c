/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktgri <ktgri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2020/06/25 16:14:55 by ktgri            ###   ########.fr       */
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
	#ifdef CL_VERSION_2_0
	ren->queue = clCreateCommandQueueWithProperties(ocl->context,
		ocl->device, 0, &err);
	#else
	ren->queue = clCreateCommandQueue(ocl->context,
		ocl->device, 0, &err);
	#endif
	ren->render_kernel = clCreateKernel(ren->program, "k_render", &err);
	if (OCL_ERROR(err, "Failed to create queue"))
		return (0);
	return (1);
}

void		delete_linked_light(t_app *app)
{
	t_light *light;

	while (app->light_list)
	{
		light = app->light_list->content;
		ft_bzero(light, app->light_list->content_size);
		app->light_list = app->light_list->next;
	}
}

void		delete_linked_obj(t_app *app)
{
	t_obj *obj;

	while (app->obj_list)
	{
		obj = app->obj_list->content;
		ft_bzero(obj, app->obj_list->content_size);
		app->obj_list = app->obj_list->next;
	}
}

void		delete_renderer(t_renderer *ren)
{
	ren->queue ? clReleaseCommandQueue(ren->queue) : 0;
	ren->program ? clReleaseProgram(ren->program) : 0;
	free_buffer(&ren->index_buf);
	free_buffer(&ren->light_buf);
	free_buffer(&ren->obj_buf);
	free_tx_buffer(&ren->color_buf);
	free_tx_buffer(&ren->normal_buf);
	free_tx_buffer(&ren->depth_buf);
	rt_tab_free(ren->src);
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
	if (OCL_ERROR(err, "Failed to enqueue kernel!"))
		return (0);
	if (OCL_ERROR(clFinish(ren->queue), "Failed to finish queue!"))
		return (0);
	return (1);
}

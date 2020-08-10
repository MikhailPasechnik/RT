/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 12:27:18 by bnesoi            #+#    #+#             */
/*   Updated: 2020/08/10 17:32:32 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline int		app_error(const char *msg, int returns)
{
	ft_fprintf(2, "Application error: %s\n", msg);
	return (returns);
}

static int		app_set_kernel_buffers(t_app *app)
{
	if (OCL_ERROR2(clSetKernelArg(app->ren.render_kernel,
		RT_K_COLOR_ARG, sizeof(cl_mem), &app->ren.color_buf.device)))
		return (app_error("failed to set kernel color buffer argument", 0));
	if (OCL_ERROR2(clSetKernelArg(app->ren.render_kernel,
			RT_K_NORMA_ARG, sizeof(cl_mem), &app->ren.normal_buf.device)))
		return (app_error("failed to set kernel normal buffer argument", 0));
	if (OCL_ERROR2(clSetKernelArg(app->ren.render_kernel,
			RT_K_DEPTH_ARG, sizeof(cl_mem), &app->ren.depth_buf.device)))
		return (app_error("failed to set kernel depth buffer argument", 0));
	if (OCL_ERROR2(clSetKernelArg(app->ren.render_kernel,
		RT_K_INDEX_ARG, sizeof(cl_mem), &app->ren.index_buf.device)))
		return (app_error("failed to set kernel index buffer argument", 0));
	if (OCL_ERROR2(clSetKernelArg(app->ren.pproc_kernel,
		1, sizeof(cl_mem), &app->ren.color_buf.device)))
		return (app_error("failed to set kernel color buffer argument", 0));
	if (OCL_ERROR2(clSetKernelArg(app->ren.pproc_kernel,
		2, sizeof(cl_mem), &app->ren.normal_buf.device)))
		return (app_error("failed to set kernel normal buffer argument", 0));
	if (OCL_ERROR2(clSetKernelArg(app->ren.pproc_kernel,
		3, sizeof(cl_mem), &app->ren.depth_buf.device)))
		return (app_error("failed to set kernel depth buffer argument", 0));
	if (OCL_ERROR2(clSetKernelArg(app->ren.pproc_kernel,
		4, sizeof(cl_mem), &app->ren.index_buf.device)))
		return (app_error("failed to set kernel index buffer argument", 0));
	if (OCL_ERROR2(clSetKernelArg(app->ren.pproc_kernel,
		5, sizeof(cl_mem), &app->ren.color_buf2.device)))
		return (app_error("failed to set kernel color2 buffer argument", 0));
	return (1);
}

int				app_update_buffers(t_app *app)
{
	size_t	size;

	size = app->op.width * app->op.height;
	app->ren.color_buf.valid ? free_tx_buffer(&app->ren.color_buf) : 0;
	app->ren.color_buf2.valid ? free_tx_buffer(&app->ren.color_buf) : 0;
	app->ren.index_buf.valid ? free_buffer(&app->ren.index_buf) : 0;
	app->ren.depth_buf.valid ? free_buffer(&app->ren.depth_buf) : 0;
	app->ren.normal_buf.valid ? free_buffer(&app->ren.normal_buf) : 0;
	app->ren.color_buf = create_tx_buffer(app, app->op.width, app->op.height,
			CL_MEM_WRITE_ONLY);
	if (!app->ren.color_buf.valid && free_tx_buffer(&app->ren.color_buf))
		return (app_error("Failed to allocate color buffer!", 0));
	app->ren.color_buf2 = create_tx_buffer(app, app->op.width, app->op.height,
			CL_MEM_WRITE_ONLY);
	if (!app->ren.color_buf2.valid && free_tx_buffer(&app->ren.color_buf2))
		return (app_error("Failed to allocate color2 buffer!", 0));
	app->ren.depth_buf = create_buffer(app->ocl.context,
		size * sizeof(cl_float), CL_MEM_WRITE_ONLY);
	if (!app->ren.depth_buf.valid && free_buffer(&app->ren.depth_buf))
		return (app_error("Failed to allocate depth buffer!", 0));
	app->ren.normal_buf = create_buffer(app->ocl.context,
		size * sizeof(cl_float3), CL_MEM_WRITE_ONLY);
	if (!app->ren.normal_buf.valid && free_tx_buffer(&app->ren.normal_buf))
		return (app_error("Failed to allocate normal buffer!", 0));
	app->ren.index_buf = create_buffer(app->ocl.context,
			size * sizeof(t_int), CL_MEM_WRITE_ONLY);
	if (!app->ren.index_buf.valid && free_buffer(&app->ren.index_buf))
		return (app_error("Failed to allocate index buffer!", 0));
	return (app_set_kernel_buffers(app));
}

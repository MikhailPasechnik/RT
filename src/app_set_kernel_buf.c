/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_set_kernel_buf.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvernius <cvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 18:50:19 by cvernius          #+#    #+#             */
/*   Updated: 2020/08/10 19:11:26 by cvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		app_set_main_kernel(t_app *app)
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
	if (OCL_ERROR2(clSetKernelArg(app->ren.render_kernel,
		RT_K_SEED_ARG, sizeof(cl_mem), &app->ren.seed_buf.device)))
		return (app_error("failed to set kernel seed buffer argument", 0));
	if (OCL_ERROR2(clSetKernelArg(app->ren.render_kernel,
		RT_K_MC_ARG, sizeof(cl_mem), &app->ren.mc_buf.device)))
		return (app_error("failed to set kernel mc buffer argument", 0));
	if (OCL_ERROR2(clSetKernelArg(app->ren.render_kernel,
		RT_K_UV_ARG, sizeof(cl_mem), &app->ren.uv_buf.device)))
		return (app_error("failed to set kernel uv buffer argument", 0));
	return (1);
}

static int		app_set_post_proc_kernel(t_app *app)
{
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
	if (OCL_ERROR2(clSetKernelArg(app->ren.pproc_kernel,
		6, sizeof(cl_mem), &app->ren.uv_buf.device)))
		return (app_error("failed to set kernel uv buffer argument", 0));
	return (1);
}

int				app_set_kernel_buffers(t_app *app)
{
	return (app_set_main_kernel(app) && app_set_post_proc_kernel(app));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvernius <cvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 12:27:18 by bnesoi            #+#    #+#             */
/*   Updated: 2020/08/10 18:53:12 by cvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline int		app_error(const char *msg, int returns)
{
	ft_fprintf(2, "Application error: %s\n", msg);
	return (returns);
}

void			app_free_all_buffers(t_app *app)
{
	app->ren.color_buf.valid ? free_tx_buffer(&app->ren.color_buf) : 0;
	app->ren.color_buf2.valid ? free_tx_buffer(&app->ren.color_buf2) : 0;
	app->ren.index_buf.valid ? free_buffer(&app->ren.index_buf) : 0;
	app->ren.depth_buf.valid ? free_buffer(&app->ren.depth_buf) : 0;
	app->ren.normal_buf.valid ? free_buffer(&app->ren.normal_buf) : 0;
	app->ren.seed_buf.valid ? free_buffer(&app->ren.seed_buf) : 0;
	app->ren.mc_buf.valid ? free_buffer(&app->ren.mc_buf) : 0;
	app->ren.uv_buf.valid ? free_buffer(&app->ren.uv_buf) : 0;
}

static int		app_update_buffers1(size_t size, t_app *app)
{
	app->ren.seed_buf = create_buffer(app->ocl.context,
									  size * sizeof(cl_uint2), CL_MEM_READ_WRITE);
	if (!app->ren.seed_buf.valid && free_buffer(&app->ren.seed_buf))
		return (app_error("Failed to allocate seed buffer!", 0));
	app->ren.mc_buf = create_buffer(app->ocl.context,
									size * sizeof(cl_float3), CL_MEM_READ_WRITE);
	if (!app->ren.mc_buf.valid && free_buffer(&app->ren.mc_buf))
		return (app_error("Failed to allocate seed buffer!", 0));
	app->ren.uv_buf = create_buffer(app->ocl.context,
									size * sizeof(cl_float2), CL_MEM_READ_WRITE);
	if (!app->ren.uv_buf.valid && free_buffer(&app->ren.uv_buf))
		return (app_error("Failed to allocate uv buffer!", 0));
}
int				app_update_buffers(t_app *app)
{
	size_t	size;

	size = app->op.width * app->op.height;
	app_free_all_buffers(app);
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
	if (!app->ren.normal_buf.valid && free_buffer(&app->ren.normal_buf))
		return (app_error("Failed to allocate normal buffer!", 0));
	app->ren.index_buf = create_buffer(app->ocl.context,
			size * sizeof(t_int), CL_MEM_WRITE_ONLY);
	if (!app->ren.index_buf.valid && free_buffer(&app->ren.index_buf))
		return (app_error("Failed to allocate index buffer!", 0));
	return (app_update_buffers1(size, app) && app_set_kernel_buffers(app));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2020/08/05 16:49:12 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static int	app_pre_render(t_app *app)
{
	if ((app->ren.width != app->op.width || app->ren.height != app->op.height))
		if (!app_update_buffers(app))
			return (app_error("Buffers update failed!", 0));
	app->ren.width = app->op.width;
	app->ren.height = app->op.height;
	if (app->cm_changed &&
		!update_camera(app->ren.render_kernel, &app->cam, RT_K_CAMERA_ARG))
		return (0);
	app->cm_changed = 0;
	if (app->op_changed &&
		!update_options(app->ren.render_kernel, &app->op, RT_K_OPTIONS_ARG))
		return (0);
	app->op_changed = 0;
	return (1);
}

int			app_render(t_app *app)
{
	t_tx_buffer *current;

	if (app->render_buffer == RT_K_COLOR_ARG)
		current = &app->ren.color_buf;
	else if (app->render_buffer == RT_K_NORMA_ARG)
		current = &app->ren.normal_buf;
	else if (app->render_buffer == RT_K_DEPTH_ARG)
		current = &app->ren.depth_buf;
	else
		current = &app->ren.color_buf;
	if (!app_pre_render(app))
		return (app_error("Failed to setup render!", 0));
	if (!render(&app->ren, &app->ocl))
		return (app_error("Failed to render!", 0));
	if (!pull_tx_buffer(app->ren.queue, current, 0))
		return (app_error("Failed to pull color buffer!", 0));
	if (!pull_buffer(app->ren.queue, &app->ren.index_buf,
			app->ren.index_buf.size, 0))
		return (app_error("Failed to pull index buffer!", 0));
	SDL_RenderCopy(app->renderer, current->host, NULL,
		&(SDL_Rect){.y=0, .x=0, .h=app->op.height, .w=app->op.width});
	SDL_RenderPresent(app->renderer);
	return (1);
}

int			app_start(t_app *app, char **argv, int argc)
{
	(void)argv;
	(void)argc;
	app->op_changed = 1;
	app->cm_changed = 1;
	app->selection = -1;
	app->render_buffer = RT_K_COLOR_ARG;
	init_options(&app->op);
	if (!(ocl_init(&app->ocl)))
		return (app_error("Failed to initialise OpenCL", 0));
	if (!new_renderer(&app->ren, &app->ocl, RT_CL_SRC, RT_CL_INCLUDE))
		return (app_error("Failed to create renderer", 0));
	if (!(app->win = SDL_CreateWindow(
			RT_WIN_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			app->op.width, app->op.height, RT_WIN_FLAGS)))
		return (app_error(SDL_GetError(), 0));
	if (!(app->renderer = SDL_CreateRenderer(app->win, -1,
			SDL_RENDERER_ACCELERATED)))
		return (app_error(SDL_GetError(), 0));
	if (!transfer_objects(app) || !transfer_light(app))
		return (app_error("Scene transfer failed!", 0));
	ft_lstreverse(&app->tx_info_list);
	ft_lstreverse(&app->tx_src_list);
	if (!transfer_textures(app) || !transfer_texture_info(app))
		return (app_error("Texture transfer failed!", 0));
	nav_rotate_camera(&app->cam, &VEC(0, 0, 0), &VEC(0, 0, 0));
	return (app_render(app));
}

void		app_finish(t_app *app)
{
	delete_renderer(&app->ren);
	SDL_DestroyRenderer(app->renderer);
	app_delete_linked_lists(app);
	app->win ? SDL_DestroyWindow(app->win) : 0;
	ocl_release(&app->ocl);
}

void		on_app_event(t_app *app, SDL_Event *event)
{
	int changed;

	changed = 0;
	if (event->type == SDL_WINDOWEVENT &&
		event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		on_window_size_change(&event->window, app, &changed);
	else if (event->type == SDL_MOUSEMOTION)
		on_mouse_move(&event->motion, app, &changed);
	else if (event->type == SDL_MOUSEWHEEL)
		on_mouse_wheel(&event->wheel, app, &changed);
	else if (event->type == SDL_KEYDOWN)
		on_key_press(&event->key, app, &changed);
	else if (event->type == SDL_MOUSEBUTTONDOWN ||
			event->type == SDL_MOUSEBUTTONUP)
		on_mouse_click(&event->button, app, &changed);
	changed ? app_render(app) : 0;
}

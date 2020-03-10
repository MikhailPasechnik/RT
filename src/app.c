/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2020/02/22 00:45:08 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"


inline int app_error(const char *msg, int returns)
{
	ft_fprintf(2, "Application error: %s\n", msg);
	return (returns);
}

static int app_pre_render(t_app *app)
{
	app->ren.width = app->op.width;
	app->ren.height = app->op.height;
	if (app->ol_changed && !transfer_objects(app))
		return (0);
	app->ol_changed = 0;
	if (app->ll_changed && !transfer_light(app))
		return (0);
	app->ll_changed = 0;
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

static int app_render(t_app *app)
{
	SDL_Surface		*surface;
	SDL_Renderer	*renderer;

	if (!app_pre_render(app))
		return (app_error("Failed to setup render!", 0));
	surface = SDL_GetWindowSurface(app->win);
	if (!render(&app->ren, &app->ocl, surface->pixels, &app->rect))
		return (app_error("Failed to render!", 0));
//	renderer = SDL_GetRenderer(app->win);
//	SDL_Rect r =  (SDL_Rect){.h = 10, .w = 10, .x = 0, .y = 0};
//	SDL_RenderDrawRect(renderer, &r);
	SDL_UpdateWindowSurface(app->win);
	return (1);
}

int				app_start(t_app *app, char **argv, int argc)
{
	app->ll_changed = 1;
	app->ol_changed = 1;
	app->op_changed = 1;
	app->cm_changed = 1;
	app->op.height = RT_WIN_HEIGHT;
	app->op.width = RT_WIN_WIDTH;

	rt_set_rect(&app->rect, 0, 0, app->op.width, app->op.height);
	if (!(ocl_init(&app->ocl)))
		return (app_error("Failed to initialise OpenCL", 0));
	if (!new_renderer(&app->ren, &app->ocl, RT_CL_SRC, RT_CL_INCLUDE))
		return (app_error("Failed to create renderer", 0));
	if (!(app->win = SDL_CreateWindow(
			RT_WIN_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			app->op.width, app->op.height, RT_WIN_FLAGS)))
		return (app_error(SDL_GetError(), 0));
	return (app_render(app));
}

void	app_finish(t_app *app)
{
	app->win ? SDL_DestroyWindow(app->win) : 0;
	delete_renderer(&app->ren);
	ocl_release(&app->ocl);
}

void	on_app_event(t_app *app, SDL_Event *event)
{
	int	changed;

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
	else if (event->type == SDL_WINDOWEVENT_ENTER ||
			event->type == SDL_WINDOWEVENT_LEAVE)
		on_mouse_focus(event, app, &changed);
	else if (event->type == SDL_MOUSEBUTTONUP ||
			event->type == SDL_MOUSEBUTTONDOWN)
		on_mouse_button(&event->button, app, &changed);
	changed ? app_render(app) : 0;
}

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

#include "rt.h"

static int app_render(t_app *app)
{
	SDL_Surface	*surface;

	app->ren.width = app->width;
	app->ren.height = app->height;
	surface = SDL_GetWindowSurface(app->win);
	if (!render(&app->ren, &app->ocl, surface->pixels, &app->rect))
		return (0);
	SDL_UpdateWindowSurface(app->win);
	return (1);
}

static int app_error(const char *msg, int returns)
{
	ft_fprintf(2, "Application error: %s\n", msg);
	return (returns);
}

int				app_start(t_app *app, char **argv, int argc)
{
	ft_bzero(app, sizeof(t_app));
	app->height = RT_WIN_HEIGHT;
	app->width = RT_WIN_WIDTH;

	rt_set_rect(&app->rect, 0, 0, app->width, app->height);
	if (!(ocl_init(&app->ocl)))
		return (app_error("Failed to initialise OpenCL", 0));
	if (!new_renderer(&app->ren, &app->ocl, RT_CL_SRC, RT_CL_INCLUDE))
		return (app_error("Failed to create renderer", 0));
	if (!(app->win = SDL_CreateWindow(
			RT_WIN_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			app->width, app->height, RT_WIN_FLAGS)))
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
	if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		on_window_size_change(&event->window, app, &changed);
	else if (event->type == SDL_MOUSEMOTION)
		on_mouse_move(&event->motion, app, &changed);
	else if (event->type == SDL_MOUSEWHEEL)
		on_mouse_wheel(&event->wheel, app, &changed);
	else if (event->type == SDL_KEYDOWN)
		on_key_press(&event->key, app, &changed);
	changed ? app_render(app) : 0;
}

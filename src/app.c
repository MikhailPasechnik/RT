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
	app->canvas = !app->canvas ? SDL_CreateTexture(app->renderer,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, app->op
			.width, app->op.height) : app->canvas;
	if (!app->canvas)
		return app_error("Failed to initialize Canvas!", 0);

	return (1);
}

void draw_circle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY,
		int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}
static int app_render(t_app *app)
{
	void		*pixels;
	int 		pitch;

	if (!app_pre_render(app))
		return (app_error("Failed to setup render!", 0));

	SDL_LockTexture(app->canvas, NULL, &pixels, &pitch);
	if (!render(&app->ren, &app->ocl, pixels, &app->rect))
		return (app_error("Failed to render!", 0));
	SDL_UnlockTexture(app->canvas);
	SDL_RenderCopy(app->renderer, app->canvas, NULL, &(SDL_Rect){.y=0, .x=0,
															  .h=app->op.height,
															  .w=app->op.width});
//	renderer = SDL_GetRenderer(app->win);
//	SDL_Rect r =  (SDL_Rect){.h = 10, .w = 10, .x = 0, .y = 0};
//	SDL_RenderDrawRect(renderer, &r);
	SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255 );
	draw_circle(app->renderer, 5, 5, 4);

	// Render the rect to the screen
	SDL_RenderPresent(app->renderer);
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
	app->op.background_color = VEC(44/255.,44/255.,44/255.);

	rt_set_rect(&app->rect, 0, 0, app->op.width, app->op.height);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 00:19:37 by bmahi             #+#    #+#             */
/*   Updated: 2020/07/23 22:45:49 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			on_mouse_move(SDL_MouseMotionEvent *event,
		t_app *app, int *changed)
{
	if (event->state & SDL_BUTTON_LMASK)
	{
		nav_rotate_camera(&app->cam,
			&VEC(event->yrel * 0, event->xrel * 0, event->xrel * 1),
			&VEC(0, 0, 0));
		app->cm_changed = 1;
		*changed = 1;
	}
}

void			on_window_size_change(SDL_WindowEvent *event,
		t_app *app, int *changed)
{
	(void)event;
	SDL_GetWindowSize(app->win, (int *)&app->op.width, (int *)&app->op.height);
	app->op_changed = 1;
	*changed = 1;
}

void			on_mouse_wheel(SDL_MouseWheelEvent *event,
		t_app *app, int *changed)
{
	nav_move_camera(&app->cam, &VEC(0, 0, event->y > 0 ? -1 : 1));
	app->cm_changed = 1;
	*changed = 1;
}

static void		on_key_press1(SDL_KeyboardEvent *event,
		t_app *app, int *changed)
{
	if (event->keysym.sym == SDLK_F1 && (*changed = 1))
		app->render_buffer = RT_K_COLOR_ARG;
	else if (event->keysym.sym == SDLK_F2 && (*changed = 1))
		app->render_buffer = RT_K_NORMA_ARG;
	else if (event->keysym.sym == SDLK_F3 && (*changed = 1))
		app->render_buffer = RT_K_DEPTH_ARG;
	else if (event->keysym.sym == SDLK_F4)
		screen_shot(app);
}

void			on_key_press(SDL_KeyboardEvent *event, t_app *app, int *changed)
{
	if (event->keysym.sym == SDLK_ESCAPE)
	{
		app->quit = 1;
		return ;
	}
	else if (event->keysym.sym == SDLK_w || event->keysym.sym == SDLK_s ||
		event->keysym.sym == SDLK_d || event->keysym.sym == SDLK_a ||
		event->keysym.sym == SDLK_q || event->keysym.sym == SDLK_e)
	{
		nav_move_camera(&app->cam, &VEC(
		(event->keysym.sym == SDLK_d || event->keysym.sym == SDLK_a)
				* (event->keysym.sym == SDLK_d ? 0.3 : -0.3),
				(event->keysym.sym == SDLK_q || event->keysym.sym == SDLK_e)
				* (event->keysym.sym == SDLK_q ? 0.3 : -0.3),
				(event->keysym.sym == SDLK_w || event->keysym.sym == SDLK_s)
				* (event->keysym.sym == SDLK_w ? 0.3 : -0.3)));
		app->cm_changed = 1;
		*changed = 1;
	}
	on_key_press1(event, app, changed);
}

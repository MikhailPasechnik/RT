/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_selection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:13:17 by bnesoi            #+#    #+#             */
/*   Updated: 2020/07/23 23:10:08 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	on_scene_click_single(SDL_MouseButtonEvent *event, t_app *app,
	int *changed)
{
	t_int	i;

	i = ((t_int *)app->ren.index_buf.host)[event->y * app->op.width + event->x];
	app->selection = i;
	app->op_changed = 1;
	app->op.selection = i;
	*changed = 1;
}

void		on_mouse_click(SDL_MouseButtonEvent *event, t_app *app,
	int *changed)
{
	if (event->type == SDL_MOUSEBUTTONDOWN)
		app->ts_mouse_down = event->timestamp;
	if (event->type == SDL_MOUSEBUTTONUP &&
		event->timestamp - app->ts_mouse_down < RT_CLICK_THRESHOLD)
		on_scene_click_single(event, app, changed);
}

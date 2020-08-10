/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_selection_loop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 16:20:36 by bmahi             #+#    #+#             */
/*   Updated: 2020/08/10 16:24:37 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	gui_selection_loop(t_app *app, t_gui *gui)
{
	t_uint			changed;
	t_obj			*o;

	changed = 0;
	if (nk_begin(gui->ctx, "Selection", nk_rect(0, 0, GUI_WIN_WIDTH / 2,
		GUI_WIN_HEIGHT), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE |
		NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		if (app->selection != -1)
		{
			o = &((t_obj*)app->ren.obj_buf.host)[app->selection];
			changed |= gui_vec_pick(&o->pos, "Position:", gui->ctx);
			changed |= gui_vec_pick(&o->rot, "Rotation:", gui->ctx);
			changed |= gui_single_pick(&o->height, "Height:", gui->ctx);
			changed |= gui_single_pick(&o->radius, "Radius:", gui->ctx);
			changed |= gui_color_pick(&o->mat.diff, "Diffuse:", gui->ctx);
			changed |= gui_gray_pick(&o->mat.specular, "Specular:", gui->ctx);
			changed |= gui_gray_pick(&o->mat.reflection, "Reflection:",
				gui->ctx);
			if (changed)
				push_buffer(app->ren.queue, &app->ren.obj_buf,
					app->ren.obj_buf.size, 0) && app_render(app);
		}
	}
	nk_end(gui->ctx);
}

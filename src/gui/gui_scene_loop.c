/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_scene_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvernius <cvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 16:18:57 by bmahi             #+#    #+#             */
/*   Updated: 2020/08/10 19:25:06 by cvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void			gui_end_loop(t_app *app, t_gui *gui)
{
	(void)app;
	SDL_GL_MakeCurrent(gui->win, gui->gl_context);
	glViewport(0, 0, GUI_WIN_WIDTH, GUI_WIN_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT);
	nk_sdl_render(NK_ANTI_ALIASING_ON, GUI_MAX_VERTEX_MEMORY,
		GUI_MAX_ELEMENT_MEMORY);
	SDL_GL_SwapWindow(gui->win);
}

static void		gui_post_proc_loop(t_app *app, t_gui *gui, unsigned int *change)
{
	!app->op.mc ? gui_isingle_pick(&app->op.target_samples, "#MC Samples:", gui->ctx) : 0;
	if (nk_button_label(gui->ctx, "Monte Carlo") || app->op.mc)
	{
		app->op.mc = 1;
		app->op.sample_step = 4;
		(app->op_changed = 1) && app_render(app);
		app->op.current_sample += app->op.sample_step;
		ft_printf("Rendering %d / %d\n", app->op.current_sample, app->op.target_samples);
		nk_prog(gui->ctx, (nk_size)app->op.current_sample, app->op.target_samples, 0);
		if (nk_button_label(gui->ctx, "Stop!") || app->op.current_sample >= app->op.target_samples)
		{
			app->op.current_sample = 0;
			app->op.mc = 0;
			update_options(app->ren.render_kernel, &app->op, RT_K_OPTIONS_ARG);
		}
	}
	*change |= nk_checkbox_label(gui->ctx, "Post processing",
								&app->ren.pproc_enabled);
	if (app->ren.pproc_enabled)
	{
		*change |= nk_checkbox_label(gui->ctx, "FXAA", &app->op.fxaa);
		*change |= nk_checkbox_label(gui->ctx, "DOF", &app->op.dof);
		if (app->op.dof)
		{
			nk_label(gui->ctx, "Dof focal point:", NK_TEXT_LEFT);
			*change |= nk_slider_float(gui->ctx, 1, &app->op.dof_focal_point,
										100, 0.01f);
			nk_label(gui->ctx, "Dof strength:", NK_TEXT_LEFT);
			*change |= nk_slider_float(gui->ctx, 1, &app->op.dof_strength,
										100, 0.01f);
		}
		*change |= nk_checkbox_label(gui->ctx, "Edge effect",
									&app->op.edge_effect);
		if (app->op.edge_effect)
			*change |= gui_color_pick(&app->op.edge_color, "Edge color:",
										gui->ctx);
	}
}

void			gui_scene_loop(t_app *app, t_gui *gui)
{
	unsigned int change;

	change = 0;
	if (nk_begin(gui->ctx, "Scene", nk_rect(GUI_WIN_WIDTH / 2, 0,
		GUI_WIN_WIDTH / 2, GUI_WIN_HEIGHT / 2),
		NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
		NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		nk_layout_row_dynamic(gui->ctx, 20, 1);
		if (nk_button_label(gui->ctx, "Save Scene"))
			save_scene(app);
		if (nk_button_label(gui->ctx, "Screenshot"))
			screen_shot(app);
		change |= nk_checkbox_label(gui->ctx, "Sepia", &app->op.sepia);
		nk_label(gui->ctx, "Reflection depth:", NK_TEXT_LEFT);
		change |= nk_slider_int(gui->ctx, 1, &app->op.ref_depth,
			REF_DEPTH_MAX, 1);
		change |= gui_color_pick(&app->op.background_color, "Background color:",
			gui->ctx);
		gui_post_proc_loop(app, gui, &change);
		if (change)
			(app->op_changed = 1) && app_render(app);
	}
	nk_end(gui->ctx);
}

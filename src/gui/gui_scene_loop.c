#include "gui.h"

void	gui_end_loop(t_app *app, t_gui *gui)
{
	(void)app;
	SDL_GL_MakeCurrent(gui->win, gui->gl_context);
	glViewport(0, 0, GUI_WIN_WIDTH, GUI_WIN_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT);
	nk_sdl_render(NK_ANTI_ALIASING_ON, GUI_MAX_VERTEX_MEMORY,
				  GUI_MAX_ELEMENT_MEMORY);
	SDL_GL_SwapWindow(gui->win);
}

void	gui_scene_loop(t_app *app, t_gui *gui)
{
	unsigned int change;

	change = 0;
	if (nk_begin(gui->ctx, "Scene", nk_rect(GUI_WIN_WIDTH / 2, 0,
											GUI_WIN_WIDTH / 2, GUI_WIN_HEIGHT / 2),
				 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
				 NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		nk_layout_row_static(gui->ctx, 30, 180, 1);
		if (nk_button_label(gui->ctx, "Save"))
			save_scene(app);
		change |= nk_checkbox_label(gui->ctx, "Sepia", &app->op.sepia);
		change |= nk_checkbox_label(gui->ctx, "Post processing", &app->ren.pproc_enabled);
		if (app->ren.pproc_enabled)
		{
			change |= nk_checkbox_label(gui->ctx, "FXAA", &app->op.fxaa);
			change |= nk_checkbox_label(gui->ctx, "DOF", &app->op.dof);
			if (app->op.dof)
			{
				nk_label(gui->ctx, "Dof focal point:", NK_TEXT_LEFT);
				change |= nk_slider_float(gui->ctx, 1, &app->op.dof_focal_point, 100, 0.01f);
				nk_label(gui->ctx, "Dof strength:", NK_TEXT_LEFT);
				change |= nk_slider_float(gui->ctx, 1, &app->op.dof_strength, 100, 0.01f);
			}
			change |= nk_checkbox_label(gui->ctx, "Edge effect", &app->op.edge_effect);
			if (app->op.edge_effect)
				change |= gui_color_pick(&app->op.edge_color, "Edge color:", gui->ctx);
		}
		nk_label(gui->ctx, "Reflection depth:", NK_TEXT_LEFT);
		change |= nk_slider_int(gui->ctx, 1, &app->op.ref_depth, REF_DEPTH_MAX, 1);
		change |= gui_color_pick(&app->op.background_color, "Background color:", gui->ctx);
		if (change)
			(app->op_changed = 1) && app_render(app);
	}
	nk_end(gui->ctx);
}

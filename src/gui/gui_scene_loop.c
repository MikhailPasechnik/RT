#include "gui.h"

void	gui_scene_loop(t_app *app, t_gui *gui)
{
	if (nk_begin(gui->ctx, "Scene", nk_rect(GUI_WIN_WIDTH / 2, 0,
											GUI_WIN_WIDTH / 2, GUI_WIN_HEIGHT / 2),
				 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
				 NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		nk_layout_row_static(gui->ctx, 30, 180, 1);
		if (nk_button_label(gui->ctx, "Save"))
			save_scene(app);
		if (nk_checkbox_label(gui->ctx, "Sepia", &app->op.sepia))
			update_options(app->ren.render_kernel, &app->op, RT_K_OPTIONS_ARG) && app_render(app);
		nk_label(gui->ctx, "Reflection Depth:", NK_TEXT_LEFT);
		if (nk_slider_int(gui->ctx, 1, &app->op.ref_depth, REF_DEPTH_MAX, 1))
			update_options(app->ren.render_kernel, &app->op, RT_K_OPTIONS_ARG) && app_render(app);
	}
	nk_end(gui->ctx);
}

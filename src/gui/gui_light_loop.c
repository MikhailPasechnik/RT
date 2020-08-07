#include "gui.h"

void	gui_light_loop(t_app *app, t_gui *gui)
{
	t_uint			changed;
	t_light 		*l;
	int				i;


	if (nk_begin(gui->ctx, "Lights", nk_rect(GUI_WIN_WIDTH / 2, 0,
											 GUI_WIN_WIDTH / 2, GUI_WIN_HEIGHT),
				 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
				 NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		i = 0;
		changed = 0;
		char name[20];
		while (i < app->op.light_count)
		{
			l = &((t_light *)app->ren.light_buf.host)[i];
			ft_sprintf(name, "Light%d", i);
			nk_layout_row_dynamic(gui->ctx, 20, 1);
			nk_label(gui->ctx, name, NK_TEXT_LEFT);
			nk_layout_row_dynamic(gui->ctx, 25, 1);
			ft_sprintf(name, "Light%d:Color:", i);
			changed |= gui_color_pick(&l->color, name, gui->ctx);
			ft_sprintf(name, "Light%d:Intensity:", i);
			changed |= gui_single_pick(&l->intensity, name, gui->ctx);
			ft_sprintf(name, "Light%d:Position:", i);
			changed |= gui_vec_pick(&l->pos, name, gui->ctx);
			ft_sprintf(name, "Light%d:Rotation:", i);
			changed |= gui_vec_pick(&l->rot, name, gui->ctx);
			i++;
		}
		if (changed)
		{
			push_buffer(app->ren.queue, &app->ren.light_buf,
						app->ren.light_buf.size, 0);
			app_render(app);
		}
	}
	nk_end(gui->ctx);
}

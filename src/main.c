/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2020/07/08 19:43:55 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** We must define NK_IMPLEMENTATION and NK_SDL_GL3_IMPLEMENTATION in one .c file
*/
#define NK_IMPLEMENTATION
#define NK_SDL_GL3_IMPLEMENTATION


#include "rt.h"
#include "gui.h"

int		sdl_init(void)
{
	SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS) < 0)
	{
		ft_putendl_fd("Failed to init SDL! SDL_Error: ", 2);
		ft_putendl_fd(SDL_GetError(), 2);
		return (0);
	}
	return (1);
}

void	sdl_loop(t_app *app, t_gui *gui)
{
	SDL_Event	event;
	int			quit;

	quit = 0;
	while (!quit)
	{
		nk_input_begin(gui->ctx);
		while (SDL_PollEvent(&event))
		{
			quit = event.type == SDL_QUIT;
			if (SDL_GetWindowID(app->win) == event.window.windowID)
			{
				on_app_event(app, &event);
			} else if (SDL_GetWindowID(gui->win) == event.window.windowID)
			{
				nk_sdl_handle_event(&event);
			}
			quit = quit || app->quit;
		}
		nk_input_end(gui->ctx);

		/* GUI */
		if (nk_begin(gui->ctx, "Demo", nk_rect(50, 50, 230, 250),
					 NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
					 NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
		{
			enum {EASY, HARD};
			static int op = EASY;
			static int property = 20;

			nk_layout_row_static(gui->ctx, 30, 80, 1);
			if (nk_button_label(gui->ctx, "button"))
				printf("button pressed!\n");
			nk_layout_row_dynamic(gui->ctx, 30, 2);
			if (nk_option_label(gui->ctx, "easy", op == EASY)) op = EASY;
			if (nk_option_label(gui->ctx, "hard", op == HARD)) op = HARD;
			nk_layout_row_dynamic(gui->ctx, 22, 1);
			nk_property_int(gui->ctx, "Compression:", 0, &property, 100, 10, 1);
			if (app->selection != -1) {
				t_obj* o = &((t_obj*)app->ren.obj_buf.host)[app->selection];
				struct nk_colorf tmp = (struct nk_colorf){o->mat.diff.x, o->mat.diff.y, o->mat.diff.z};
				nk_layout_row_dynamic(gui->ctx, 20, 1);
				nk_label(gui->ctx, "background:", NK_TEXT_LEFT);
				nk_layout_row_dynamic(gui->ctx, 25, 1);
				if (nk_combo_begin_color(gui->ctx, nk_rgb_cf(tmp), nk_vec2(nk_widget_width(gui->ctx),400))) {
					nk_layout_row_dynamic(gui->ctx, 120, 1);
					tmp = nk_color_picker(gui->ctx, tmp, NK_RGB);
					nk_combo_end(gui->ctx);
				}
				if (!CMP_CLR(tmp.r, tmp.g, tmp.b, o->mat.diff.x, o->mat.diff.y, o->mat.diff.z))
				{
					o->mat.diff = COLOR(tmp.r, tmp.g, tmp.b, tmp.a);
					push_buffer(app->ren.queue, &app->ren.obj_buf, app->ren.obj_buf.size, 0);
					app_render(app);
				}
			}
		}
		nk_end(gui->ctx);
		SDL_GL_MakeCurrent(gui->win, gui->glContext);
		glViewport(0, 0, GUI_WIN_WIDTH, GUI_WIN_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT);
		nk_sdl_render(NK_ANTI_ALIASING_ON, GUI_MAX_VERTEX_MEMORY, GUI_MAX_ELEMENT_MEMORY);
		SDL_GL_SwapWindow(gui->win);
	}
}

int		setup_gui(t_app *app, t_gui *gui)
{
	return (gui_setup(gui));
}

int		main(int argc, char **argv)
{
	t_app app;
	t_gui gui;

	if (argc > 2)
		return (app_error("Too much arguments! RT || RT scene/name\n", 1));
	ft_bzero(&app, sizeof(t_app));
	parser(&app, argc > 1 ? argv[1] : "./scene/simple.yml");
	!sdl_init() ? exit(1) : 0;
	if (!app_start(&app, argv + 1, argc - 1) || !setup_gui(&app, &gui))
		app_finish(&app);
	else
	{
		sdl_loop(&app, &gui);
		app_finish(&app);
	}
	SDL_Quit();
	return (0);
}

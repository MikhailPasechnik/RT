/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2020/08/05 19:36:58 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** We must define NK_IMPLEMENTATION and NK_SDL_GL3_IMPLEMENTATION in one .c file
*/
#define NK_IMPLEMENTATION
#define NK_SDL_GL3_IMPLEMENTATION
/*
** We must define STB_IMAGE_IMPLEMENTATION in one .c file for single header lib
*/
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "gui.h"
#include "rt.h"

int		sdl_init(void)
{
	SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) < 0)
	{
		ft_putendl_fd("Failed to init SDL! SDL_Error: ", 2);
		ft_putendl_fd(SDL_GetError(), 2);
		return (0);
	}
	return (1);
}

void	sdl_loop(t_app *app, t_gui *gui)
{
	SDL_Event		event;
	int				quit;

	quit = 0;
	while (!quit)
	{
		nk_input_begin(gui->ctx);
		while (SDL_PollEvent(&event))
		{
			quit = event.type == SDL_QUIT;
			if (SDL_GetWindowID(app->win) == event.window.windowID)
				on_app_event(app, &event);
			else if (SDL_GetWindowID(gui->win) == event.window.windowID)
				nk_sdl_handle_event(&event);
			quit = quit || app->quit;
		}
		nk_input_end(gui->ctx);
		gui_selection_loop(app, gui);
		gui_light_loop(app, gui);
		gui_scene_loop(app, gui);
		gui_end_loop(app, gui);
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
	parser(&app, argc > 1 ? argv[1] : "./scene/cubism.yml");
	!sdl_init() ? exit(1) : 0;
	if (!app_start(&app, argv + 1, argc - 1) || !setup_gui(&app, &gui))
	{
		gui_destroy(&gui);
		app_finish(&app);
	}
	else
	{
		sdl_loop(&app, &gui);
		gui_destroy(&gui);
		app_finish(&app);
	}
	SDL_Quit();
	return (0);
}

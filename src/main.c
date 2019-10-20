/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2019/06/21 12:52:38 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		sdl_init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		ft_putendl_fd("Failed to init SDL! SDL_Error: ", 2);
		ft_putendl_fd(SDL_GetError(), 2);
		return (0);
	}
	return (1);
}

void	sdl_loop(t_app *app)
{
	SDL_Event	event;
	int			quit;

	quit = 0;
	while (!quit)
		while (SDL_PollEvent(&event))
		{
			quit = event.type == SDL_QUIT;
			if (SDL_GetWindowID(app->win) == event.window.windowID)
				on_app_event(app, &event);
			quit = quit || app->quit;
		}
}

int main(int argc, char **argv)
{
	t_app app;
	!sdl_init() ? exit(1) : 0;
	if (!app_start(&app, argv + 1, argc - 1))
		app_finish(&app);
	else
	{
		sdl_loop(&app);
		app_finish(&app);
	}
	SDL_Quit();
	return (0);
}

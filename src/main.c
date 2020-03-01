/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2020/03/01 20:37:44 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

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
	t_app	*app;
	t_light	*l;
	t_obj	*o;
//	t_cl	*cl;
	
	if (argc != 2 || !argv[1])
		kill("usage: ./RTv1 scene");
	if (!(app = (t_app *)malloc(sizeof(t_app))))
		kill("dropp malloc");
	
	parser(app, argv[1]);
	printf("Loading...\n\nlines in file = %d\nlights = %d\nobjects = %d\nOBJ_ID:\n1 - sphere\n2 - plane\n3 - cylinder\n4 - cone\n\ncamera position:\nx: %g, y: %g, z: %g\n\n",
		app->lines, app->light_sum, app->obj_sum, app->cam.pos.x_pos,
		app->cam.pos.y_pos, app->cam.pos.z_pos);
	l = app->light;
	while (l)
	{
		printf("light position:	[%g, %g, %g]\nlight color:	[%d, %d, %d]\nintensity = %g\n\n",
			l->vec_pos.x_pos, l->vec_pos.y_pos, l->vec_pos.z_pos,l->color.r,
			l->color.g, l->color.b, l->inten);
		l = l->next;			
	}
	o = app->obj;
	while (o)
	{
		if (o->name == ID_SPH)
			printf("OBJ_ID = %d\nobj position:	[%g, %g, %g]\nobj color:	[%d, %d, %d]\nradius = %g\nspecularity = %g\nreflective = %g\n\n",
				o->name, o->vec_pos.x_pos, o->vec_pos.y_pos, o->vec_pos.z_pos,
				o->color.r, o->color.g, o->color.b, o->r, o->specul, o->reflect);
		else if (o->name == ID_CON || o->name == ID_CYL)
			printf("OBJ_ID = %d\nobj position:	[%g, %g, %g]\nobj color:	[%d, %d, %d]\nobj rotate:	[%g, %g, %g]\nradius = %g\nspecularity = %g\nreflective = %g\n\n",
				o->name, o->vec_pos.x_pos, o->vec_pos.y_pos, o->vec_pos.z_pos,
				o->color.r, o->color.g, o->color.b, o->vec_rot.x_pos, o->vec_rot.y_pos,
				o->vec_rot.z_pos, o->r, o->specul, o->reflect);
		else if (o->name == ID_PLN)
			printf("OBJ_ID = %d\nobj position:	[%g, %g, %g]\nobj color:	[%d, %d, %d]\nobj rotate:	[%g, %g, %g]\nspecularity = %g\nreflective = %g\n\n",
				o->name, o->vec_pos.x_pos, o->vec_pos.y_pos, o->vec_pos.z_pos,
				o->color.r, o->color.g, o->color.b, o->vec_rot.x_pos, o->vec_rot.y_pos,
				o->vec_rot.z_pos, o->specul, o->reflect);
		o = o->next;			
	}
//	cl = (t_cl*)malloc(sizeof(t_cl));
//	cl->data = (int*)malloc(sizeof(int) * RT_WIN_HEIGHT * RT_WIN_WIDTH);
	
	/*
	!sdl_init() ? exit(1) : 0;
	if (!app_start(&app, argv + 1, argc - 1))
		app_finish(&app);
	else
	{
		sdl_loop(&app);
		app_finish(&app);
	}
	SDL_Quit();
	*/
	return (0);
}

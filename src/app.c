/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2020/02/22 00:45:08 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"


static int app_error(const char *msg, int returns)
{
	ft_fprintf(2, "Application error: %s\n", msg);
	return (returns);
}

/*
** Transfer memory from CPU to GPU
** 		1. Clean up previously allocated GPU buffer and CPU array
** 		2. Copy CPU linked list to buffer
** 		3. Create GPU buffer from CPU array
*/
static int transfer_objects(t_app *app)
{
	t_obj	*obj_array;
	int		i;
	int		err;
	t_list	*it;

	if (!(obj_array = ft_memalloc(sizeof(t_obj) * app->op.obj_count)))
		return (app_error("Failed to allocate memory for objects buffer!", 0));
	app->ren.obj_mem ? clReleaseMemObject(app->ren.obj_mem) : 0;
	app->obj_array ? ft_memdel((void **)&app->obj_array) : 0;
	app->obj_array = obj_array;
	i = 0;
	it = app->obj_list;
	while (it && i < app->op.obj_count)
	{
		app->obj_array[i] = *(t_obj*)it->content;
		it = it->next;
		i++;
	}
	if (i != app->op.obj_count || it != NULL)
		return (app_error("Object count not equal to Object List length!", 0));
	app->ren.obj_mem = clCreateBuffer(app->ocl.context,
		CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR,
									  app->op.obj_count * sizeof(t_obj), app->obj_array, &err);
	err |= clSetKernelArg(app->ren.render_kernel,
						  RT_K_SCENE_ARG, sizeof(cl_mem), &app->ren.obj_mem);
	return (OCL_ERROR(err, "Failed to create gpu buffer for objects!") ? 0 : 1);
}

/*
** Transfer memory from CPU to GPU
** 		1. Clean up previously allocated GPU buffer and CPU array
** 		2. Copy CPU linked list to buffer
** 		3. Create GPU buffer from CPU array
*/
static int transfer_light(t_app *app)
{
	t_light	*light_array;
	int		i;
	int		err;
	t_list	*it;

	if (!(light_array = ft_memalloc(sizeof(t_light) * app->op.light_count)))
		return (app_error("Failed to allocate memory for lights buffer!", 0));
	app->ren.light_mem ? clReleaseMemObject(app->ren.light_mem) : 0;
	app->light_array ? ft_memdel((void **)&app->light_array) : 0;
	app->light_array = light_array;
	i = 0;
	it = app->light_list;
	while (it && i < app->op.light_count)
	{
		app->light_array[i] = *(t_light*)it->content;
		it = it->next;
		i++;
	}
	if (i != app->op.light_count || it != NULL)
		return (app_error("Light count not equal to Light List length!", 0));
	app->ren.light_mem = clCreateBuffer(app->ocl.context,
		  CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR,
										app->op.light_count * sizeof(t_light), app->light_array, &err);
	err |= clSetKernelArg(app->ren.render_kernel,
			RT_K_LIGHTS_ARG, sizeof(cl_mem), &app->ren.light_mem);
	return (OCL_ERROR(err, "Failed to create gpu buffer for lights!") ? 0 : 1);
}

static int app_pre_render(t_app *app)
{
	int err;

	err = 0;
	app->ren.width = app->op.width;
	app->ren.height = app->op.height;
	if (app->ol_changed && !transfer_objects(app))
		return 0;
	if (app->ll_changed && !transfer_light(app))
		return 0;
	if (app->cm_changed)
		err |= clSetKernelArg(app->ren.render_kernel,
			  RT_K_CAMERA_ARG, sizeof(t_cam), &app->cam);
	OCL_ERROR(err, "To set camera kernel arg!");
	if (app->op_changed)
		err |= clSetKernelArg(app->ren.render_kernel,
			  RT_K_OPTIONS_ARG, sizeof(t_options), &app->op);
	OCL_ERROR(err, "To set options kernel arg!");
	return (OCL_ERROR2(err) ? 0 : 1);
}

static int app_render(t_app *app)
{
	SDL_Surface	*surface;

	if (!app_pre_render(app))
		return (app_error("Failed to setup render!", 0));
	surface = SDL_GetWindowSurface(app->win);
	if (!render(&app->ren, &app->ocl, surface->pixels, &app->rect))
		return (app_error("Failed to render!", 0));
	SDL_UpdateWindowSurface(app->win);
	return (1);
}

int				app_start(t_app *app, char **argv, int argc)
{
	app->ll_changed = 1;
	app->ol_changed = 1;
	app->op_changed = 1;
	app->cm_changed = 1;
	app->op.height = RT_WIN_HEIGHT;
	app->op.width = RT_WIN_WIDTH;

	rt_set_rect(&app->rect, 0, 0, app->op.width, app->op.height);
	if (!(ocl_init(&app->ocl)))
		return (app_error("Failed to initialise OpenCL", 0));
	if (!new_renderer(&app->ren, &app->ocl, RT_CL_SRC, RT_CL_INCLUDE))
		return (app_error("Failed to create renderer", 0));
	if (!(app->win = SDL_CreateWindow(
			RT_WIN_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			app->op.width, app->op.height, RT_WIN_FLAGS)))
		return (app_error(SDL_GetError(), 0));
	return (app_render(app));
}

void	app_finish(t_app *app)
{
	app->win ? SDL_DestroyWindow(app->win) : 0;
	delete_renderer(&app->ren);
	ocl_release(&app->ocl);
}

void	on_app_event(t_app *app, SDL_Event *event)
{
	int	changed;

	changed = 0;
	if (event->type == SDL_WINDOWEVENT &&
		event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		on_window_size_change(&event->window, app, &changed);
	else if (event->type == SDL_MOUSEMOTION)
		on_mouse_move(&event->motion, app, &changed);
	else if (event->type == SDL_MOUSEWHEEL)
		on_mouse_wheel(&event->wheel, app, &changed);
	else if (event->type == SDL_KEYDOWN)
		on_key_press(&event->key, app, &changed);
	changed ? app_render(app) : 0;
}

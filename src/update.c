/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 12:26:55 by bnesoi            #+#    #+#             */
/*   Updated: 2020/07/27 18:50:41 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			update_object(t_app *app, int index, t_obj *obj)
{
	t_obj		*buff;

	if (obj)
	{
		buff = app->ren.obj_buf.host;
		buff[index] = *obj;
		buff->i = obj->i;
		save_scene(app, &buff[index], app->op.obj_count + 1);
	}
	return (push_buffer(app->ren.queue, &app->ren.obj_buf,
						sizeof(t_obj), sizeof(t_obj) * index));
}

int			update_light(t_app *app, int index, t_light *light)
{
	t_light		*buff;

	if (light)
	{
		buff = app->ren.light_buf.host;
		buff[index] = *light;
	}
	return (push_buffer(app->ren.queue, &app->ren.light_buf,
						sizeof(t_light), sizeof(t_light) * index));
}

int			update_camera(cl_kernel kernel, t_cam *cam, int arg_num)
{
	int err;

	err = clSetKernelArg(kernel, arg_num, sizeof(t_cam), cam);
	OCL_ERROR(err, "Failed to set camera kernel arg!");
	return (err == CL_SUCCESS);
}

int			update_options(cl_kernel kernel,
							t_options *options, int arg_num)
{
	int err;

	err = clSetKernelArg(kernel, arg_num, sizeof(t_options), options);
	OCL_ERROR(err, "Failed to set option kernel arg!");
	return (err == CL_SUCCESS);
}

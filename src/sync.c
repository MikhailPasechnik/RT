/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 12:27:03 by bnesoi            #+#    #+#             */
/*   Updated: 2020/08/05 19:15:33 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			set_kernel_arg(cl_kernel kernel,
		int arg_num, void *ptr, size_t size)
{
	return (OCL_ERROR(clSetKernelArg(kernel, arg_num, size, ptr),
		"Failed to set kernel arg!") ? 0 : 1);
}

int			transfer_objects(t_app *app)
{
	t_int		i;
	t_list		*it;
	t_buffer	buffer;

	buffer = create_buffer(app->ocl.context,
		sizeof(t_obj) * (app->op.obj_count + RT_BUF_EXTRA), CL_MEM_READ_ONLY);
	if (!buffer.valid && free_buffer(&buffer))
		return (app_error("Failed to allocate objects buffer!", 0));
	i = 0;
	it = app->obj_list;
	while (it && i++ < app->op.obj_count)
	{
		((t_obj	*)buffer.host)[i - 1] = *(t_obj *)it->content;
		save_scene(app, 0);
		it = it->next;
	}
	if (i != app->op.obj_count || it != NULL)
		return (app_error("Object count not equal to Object list length!", 0));
	if (!push_buffer(app->ren.queue, &buffer,
			sizeof(t_obj) * app->op.obj_count, 0) && free_buffer(&buffer))
		return (app_error("Failed to push objects buffer!", 0));
	free_buffer(&app->ren.obj_buf);
	app->ren.obj_buf = buffer;
	return (set_kernel_arg(app->ren.render_kernel, RT_K_OBJ_ARG,
		&buffer.device, sizeof(cl_mem)));
}

int			transfer_light(t_app *app)
{
	t_uint		i;
	t_list		*it;
	t_buffer	buffer;

	buffer = create_buffer(app->ocl.context, sizeof(t_light) *
		(app->op.light_count + RT_BUF_EXTRA), CL_MEM_READ_ONLY);
	if (!buffer.valid && free_buffer(&buffer))
		return (app_error("Failed to allocate light buffer!", 0));
	i = 0;
	it = app->light_list;
	while (it && i++ < app->op.light_count)
	{
		((t_light *)buffer.host)[i - 1] = *(t_light *)it->content;
		save_scene(app, 0);
		it = it->next;
	}
	if (i != app->op.light_count || it != NULL)
		return (app_error("Light count not equal to Light list length!", 0));
	if (!push_buffer(app->ren.queue, &buffer,
		sizeof(t_light) * app->op.light_count, 0) && free_buffer(&buffer))
		return (app_error("Failed to push light buffer!", 0));
	free_buffer(&app->ren.light_buf);
	app->ren.light_buf = buffer;
	return (set_kernel_arg(app->ren.render_kernel, RT_K_LIGHTS_ARG,
		&buffer.device, sizeof(cl_mem)));
}

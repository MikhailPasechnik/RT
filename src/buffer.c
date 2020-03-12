#include "rt.h"


t_buffer create_buffer(cl_context ctx, size_t size, unsigned int flags, int gpu_only)
{
	int			err;
	t_buffer	buffer;

	err = 0;
	buffer.cpu = !gpu_only ? ft_memalloc(size) : NULL;
	buffer.gpu = clCreateBuffer(ctx, flags, size, NULL, &err);
	OCL_ERROR2(err);
	buffer.valid = err == CL_SUCCESS && (!gpu_only || buffer.cpu != NULL);
	buffer.size = size;
	return (buffer);
}


int		free_buffer(t_buffer *buffer)
{
	if (buffer)
	{
		(buffer)->cpu ? ft_memdel(&buffer->cpu) : 0;
		(buffer)->gpu ? clReleaseMemObject(buffer->gpu) : 0;
	}
	ft_bzero(buffer, sizeof(t_buffer));
	return (1);
}

int		push_buffer(cl_command_queue queue, t_buffer *buffer,
		size_t size, size_t offset)
{
	int err;

	err = clEnqueueWriteBuffer(queue, buffer->gpu, CL_TRUE, offset, size,
							   buffer->cpu, 0, NULL, NULL);
	return (OCL_ERROR(err, "Failed to write buffer!") ? 0 : 1);
}

int		pull_buffer(cl_command_queue queue, t_buffer buffer, size_t size)
{
	return (OCL_ERROR(clEnqueueReadBuffer(
			queue, buffer.gpu, CL_TRUE, 0, size, buffer.cpu, 0, NULL, NULL
	), "Failed to pull buffer from GPU!") ? 0 : 1);
}

int		set_kernel_arg(cl_kernel kernel, int arg_num, void *ptr, size_t size)
{
	return (OCL_ERROR(clSetKernelArg(kernel, arg_num, size, ptr),
			"Failed to set kernel arg!") ? 0 : 1);
}

int		transfer_objects(t_app *app)
{
	int		i;
	t_list	*it;
	t_obj	*obj;
	t_buffer buffer;

	buffer = create_buffer(app->ocl.context,
		sizeof(t_obj) * (app->op.obj_count + RT_BUF_EXTRA), CL_MEM_READ_ONLY, 0);
	if (!buffer.valid && free_buffer(&buffer))
		return (app_error("Failed to allocate objects buffer!", 0));
	obj = buffer.cpu;
	i = 0;
	it = app->obj_list;
	while (it && i < app->op.obj_count)
	{
		obj[i] = *(t_obj*)it->content;
		it = it->next;
		i++;
	}
	if (i != app->op.obj_count || it != NULL)
		return (app_error("Object count not equal to Object list length!", 0));
	if (!push_buffer(app->ren.queue, &buffer, sizeof(t_obj) * app->op.obj_count, 0)
		&& free_buffer(&buffer))
		return (app_error("Failed to push objects buffer!", 0));
	free_buffer(&app->ren.obj_buf);
	app->ren.obj_buf = buffer;
	return (set_kernel_arg(app->ren.render_kernel, RT_K_OBJ_ARG, &buffer
	.gpu, sizeof(cl_mem)));
}

int		transfer_light(t_app *app)
{
	int		i;
	t_list	*it;
	t_light	*light;
	t_buffer buffer;

	buffer = create_buffer(app->ocl.context,
		sizeof(t_light) * (app->op.light_count + RT_BUF_EXTRA), CL_MEM_READ_ONLY, 0);
	if (!buffer.valid && free_buffer(&buffer))
		return (app_error("Failed to allocate light buffer!", 0));
	light = buffer.cpu;
	i = 0;
	it = app->light_list;
	while (it && i < app->op.light_count)
	{
		light[i] = *(t_light*)it->content;
		it = it->next;
		i++;
	}
	if (i != app->op.light_count || it != NULL)
		return (app_error("Light count not equal to Light list length!", 0));
	if (!push_buffer(app->ren.queue, &buffer,
			sizeof(t_light) *	app->op.light_count, 0) && free_buffer(&buffer))
		return (app_error("Failed to push light buffer!", 0));
	free_buffer(&app->ren.light_buf);
	app->ren.light_buf = buffer;
	return (set_kernel_arg(app->ren.render_kernel, RT_K_LIGHTS_ARG, &buffer
			.gpu, sizeof(cl_mem)));
}

int		update_object(t_app *app, int index,  t_obj *obj)
{
	t_obj *buff;

	if (obj)
	{
		buff = app->ren.obj_buf.cpu;
		buff[index] = *obj;
	}
	return (push_buffer(app->ren.queue, &app->ren.obj_buf,
			sizeof(t_obj), sizeof(t_obj) * index));
}

int		update_light(t_app *app, int index,  t_light *light)
{
	t_light *buff;

	if (light)
	{
		buff = app->ren.light_buf.cpu;
		buff[index] = *light;
	}
	return (push_buffer(app->ren.queue, &app->ren.light_buf,
			sizeof(t_light), sizeof(t_light) * index));
}

int		update_camera(cl_kernel kernel, t_cam *cam, int arg_num)
{
	int err;

	err = clSetKernelArg(kernel, arg_num, sizeof(t_cam), cam);
	OCL_ERROR(err, "Failed to set camera kernel arg!");
	return (err == CL_SUCCESS);
}

int		update_options(cl_kernel kernel, t_options *options, int arg_num)
{
	int err;

	err = clSetKernelArg(kernel, arg_num, sizeof(t_options), options);
	OCL_ERROR(err, "Failed to set option kernel arg!");
	return (err == CL_SUCCESS);
}

int		update_output_buffers(t_app *app)
{
	size_t size;

	size = app->op.width * app->op.height;
	// TODO: check if re-alloc needed checking  buffer.size and size
	app->ren.color_buf.valid ? free_buffer(&app->ren.color_buf) : 0;
	app->ren.index_buf.valid ? free_buffer(&app->ren.index_buf) : 0;
	app->ren.color_buf = create_buffer(app->ocl.context,
			size * sizeof(t_int), CL_MEM_WRITE_ONLY, 1);
	if (!app->ren.color_buf.valid && free_buffer(&app->ren.color_buf))
		return (app_error("Failed to allocate color buffer!", 0));
	app->ren.index_buf = create_buffer(app->ocl.context,
			size * sizeof(t_int), CL_MEM_WRITE_ONLY, 0);
	if (!app->ren.index_buf.valid && free_buffer(&app->ren.index_buf))
		return (app_error("Failed to allocate index buffer!", 0));
	return (1);
}

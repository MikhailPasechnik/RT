/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvernius <cvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 00:53:33 by bmahi             #+#    #+#             */
/*   Updated: 2020/08/10 21:08:18 by cvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			translate_buf(t_app *app, t_buffer buffer)
{
	free_buffer(&app->ren.texture_buf);
	app->ren.texture_buf = buffer;
	return (set_kernel_arg(app->ren.render_kernel, RT_K_TEX_ARG,
		&buffer.device, sizeof(cl_mem)));
}

t_tx_buffer	create_tx_buffer(t_app *app,
	size_t width, size_t height, unsigned int flags)
{
	int			err;
	t_tx_buffer	buffer;

	err = 0;
	buffer.host = SDL_CreateTexture(
			app->renderer, SDL_PIXELFORMAT_RGB888,
			SDL_TEXTUREACCESS_STREAMING, app->op.width, app->op.height);
	buffer.device = clCreateBuffer(app->ocl.context, flags,
			width * height * sizeof(t_uint), NULL, &err);
	OCL_ERROR2(err);
	buffer.valid = err == CL_SUCCESS && buffer.host != NULL;
	buffer.width = width;
	buffer.height = height;
	return (buffer);
}

int			free_tx_buffer(t_tx_buffer *buffer)
{
	if (buffer)
	{
		(buffer)->host ? SDL_DestroyTexture(buffer->host) : 0;
		(buffer)->device ? clReleaseMemObject(buffer->device) : 0;
		ft_bzero(buffer, sizeof(t_tx_buffer));
	}
	return (1);
}

int			push_tx_buffer(cl_command_queue queue,
		t_tx_buffer *buffer, size_t offset)
{
	int			err;
	int			pitch;
	void		*pixels;

	SDL_LockTexture(buffer->host, NULL, &pixels, &pitch);
	err = clEnqueueWriteBuffer(queue, buffer->device, CL_TRUE, offset,
		buffer->width * buffer->height * sizeof(t_uint), pixels, 0, NULL, NULL);
	SDL_UnlockTexture(buffer->host);
	return (OCL_ERROR(err,
			"Failed to push SDL_Texture to OpenCL memory!") ? 0 : 1);
}

int			pull_tx_buffer(cl_command_queue queue,
	t_tx_buffer *buffer, size_t offset)
{
	int			err;
	int			pitch;
	void		*pixels;

	SDL_LockTexture(buffer->host, NULL, &pixels, &pitch);
	err = clEnqueueReadBuffer(queue, buffer->device, CL_TRUE, offset,
		buffer->width * buffer->height * sizeof(t_uint), pixels, 0, NULL, NULL);
	SDL_UnlockTexture(buffer->host);
	return (OCL_ERROR(err,
			"Failed to pull OpenCL memory to SDL_Texture!") ? 0 : 1);
}

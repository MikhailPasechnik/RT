/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 00:10:54 by bmahi             #+#    #+#             */
/*   Updated: 2020/03/17 00:16:58 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_buffer	create_buffer(cl_context ctx, size_t size, unsigned int flags)
{
	int			err;
	t_buffer	buffer;

	err = 0;
	buffer.host = ft_memalloc(size);
	buffer.device = clCreateBuffer(ctx, flags, size, NULL, &err);
	OCL_ERROR2(err);
	buffer.valid = err == CL_SUCCESS && buffer.host != NULL;
	buffer.size = size;
	return (buffer);
}

int			free_buffer(t_buffer *buffer)
{
	if (buffer)
	{
		(buffer)->host ? ft_memdel(&buffer->host) : 0;
		(buffer)->device ? clReleaseMemObject(buffer->device) : 0;
		ft_bzero(buffer, sizeof(t_buffer));
	}
	return (1);
}

int			push_buffer(cl_command_queue queue, t_buffer *buffer,
		size_t size, size_t offset)
{
	int	err;

	err = clEnqueueWriteBuffer(queue, buffer->device, CL_TRUE, offset, size,
		buffer->host, 0, NULL, NULL);
	return (OCL_ERROR(err, "Failed to push data to OpenCL memory!") ? 0 : 1);
}

int			pull_buffer(cl_command_queue queue,
		t_buffer *buffer, size_t size, size_t offset)
{
	return (OCL_ERROR(clEnqueueReadBuffer(
		queue, buffer->device, CL_TRUE, offset, size, buffer->host,
		0, NULL, NULL), "Failed to pull OpenCL memory to host!") ? 0 : 1);
}

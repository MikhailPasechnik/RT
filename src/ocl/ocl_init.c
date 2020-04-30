/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 12:27:27 by bnesoi            #+#    #+#             */
/*   Updated: 2020/03/17 12:27:28 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

cl_device_id	ocl_create_device(void)
{
	cl_platform_id	platform_id;
	cl_device_id	device_id;
	cl_int			err;

	err = clGetPlatformIDs(1, &platform_id, NULL);
	if (OCL_ERROR(err, "Couldn't identify a platform"))
		return (NULL);
	err = clGetDeviceIDs(platform_id,
			CL_DEVICE_TYPE_CPU, 1, &device_id, NULL);
	if (OCL_ERROR(err, "No suitable device found"))
		return (NULL);
	return (device_id);
}

int				ocl_init(t_ocl *cl)
{
	cl_int	err;

	ft_bzero(cl, sizeof(*cl));
	if (!(cl->device = ocl_create_device()))
		return (0);
	cl->context = clCreateContext(NULL, 1, &cl->device, NULL, NULL, &err);
	if (OCL_ERROR(err, "Failed to create context"))
	{
		clReleaseDevice(cl->device);
		cl->device = NULL;
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvernius <cvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 12:27:23 by bnesoi            #+#    #+#             */
/*   Updated: 2020/08/10 20:25:29 by cvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl.h"

/*
** run-time and JIT compiler errors
*/

static const char	*get_error(const char *s)
{
	return (s);
}

static const char	*ocl_get_error_string3(int err)
{
	(err == 0) ? (get_error("CL_SUCCESS")) : (0);
	(err == -1) ? (get_error("CL_DEVICE_NOT_FOUND")) : 0;
	(err == -2) ? get_error("CL_DEVICE_NOT_AVAILABLE") : 0;
	(err == -3) ? get_error("CL_COMPILER_NOT_AVAILABLE") : 0;
	(err == -4) ? get_error("CL_MEM_OBJECT_ALLOCATION_FAILURE") : 0;
	(err == -5) ? get_error("CL_OUT_OF_RESOURCES") : 0;
	(err == -6) ? get_error("CL_OUT_OF_HOST_MEMORY") : 0;
	(err == -7) ? get_error("CL_PROFILING_INFO_NOT_AVAILABLE") : 0;
	(err == -8) ? get_error("CL_MEM_COPY_OVERLAP") : 0;
	(err == -9) ? get_error("CL_IMAGE_FORMAT_MISMATCH") : 0;
	(err == -10) ? get_error("CL_IMAGE_FORMAT_NOT_SUPPORTED") : 0;
	(err == -11) ? get_error("CL_BUILD_PROGRAM_FAILURE") : 0;
	(err == -12) ? get_error("CL_MAP_FAILURE") : 0;
	(err == -13) ? get_error("CL_MISALIGNED_SUB_BUFFER_OFFSET") : 0;
	(err == -14) ? get_error("CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST")
																	: 0;
	(err == -15) ? get_error("CL_COMPILE_PROGRAM_FAILURE") : 0;
	(err == -16) ? get_error("CL_LINKER_NOT_AVAILABLE") : 0;
	(err == -17) ? get_error("CL_LINK_PROGRAM_FAILURE") : 0;
	(err == -18) ? get_error("CL_DEVICE_PARTITION_FAILED") : 0;
	(err == -19) ? get_error("CL_KERNEL_ARG_INFO_NOT_AVAILABLE") : 0;
	return (NULL);
}

/*
** compile-time errors
*/

static const char	*ocl_get_error_string2(int err)
{
	(err == -30) ? get_error("CL_INVALID_VALUE") : 0;
	(err == -31) ? get_error("CL_INVALID_DEVICE_TYPE") : 0;
	(err == -32) ? get_error("CL_INVALID_PLATFORM") : 0;
	(err == -33) ? get_error("CL_INVALID_DEVICE") : 0;
	(err == -34) ? get_error("CL_INVALID_CONTEXT") : 0;
	(err == -35) ? get_error("CL_INVALID_QUEUE_PROPERTIES") : 0;
	(err == -36) ? get_error("CL_INVALID_COMMAND_QUEUE") : 0;
	(err == -37) ? get_error("CL_INVALID_HOST_PTR") : 0;
	(err == -38) ? get_error("CL_INVALID_MEM_OBJECT") : 0;
	(err == -39) ? get_error("CL_INVALID_IMAGE_FORMAT_DESCRIPTOR") : 0;
	(err == -40) ? get_error("CL_INVALID_IMAGE_SIZE") : 0;
	(err == -41) ? get_error("CL_INVALID_SAMPLER") : 0;
	(err == -42) ? get_error("CL_INVALID_BINARY") : 0;
	(err == -43) ? get_error("CL_INVALID_BUILD_OPTIONS") : 0;
	(err == -44) ? get_error("CL_INVALID_PROGRAM") : 0;
	(err == -45) ? get_error("CL_INVALID_PROGRAM_EXECUTABLE") : 0;
	(err == -46) ? get_error("CL_INVALID_KERNEL_NAME") : 0;
	(err == -47) ? get_error("CL_INVALID_KERNEL_DEFINITION") : 0;
	(err == -48) ? get_error("CL_INVALID_KERNEL") : 0;
	(err == -49) ? get_error("CL_INVALID_ARG_INDEX") : 0;
	(err == -50) ? get_error("CL_INVALID_ARG_VALUE") : 0;
	return (ocl_get_error_string3(err));
}

/*
** compile-time errors
*/

static const char	*ocl_get_error_string1(int err)
{
	(err == -50) ? get_error("CL_INVALID_ARG_VALUE") : 0;
	(err == -51) ? get_error("CL_INVALID_ARG_SIZE") : 0;
	(err == -52) ? get_error("CL_INVALID_KERNEL_ARGS") : 0;
	(err == -53) ? get_error("CL_INVALID_WORK_DIMENSION") : 0;
	(err == -54) ? get_error("CL_INVALID_WORK_GROUP_SIZE") : 0;
	(err == -55) ? get_error("CL_INVALID_WORK_ITEM_SIZE") : 0;
	(err == -56) ? get_error("CL_INVALID_GLOBAL_OFFSET") : 0;
	(err == -57) ? get_error("CL_INVALID_EVENT_WAIT_LIST") : 0;
	(err == -58) ? get_error("CL_INVALID_EVENT") : 0;
	(err == -59) ? get_error("CL_INVALID_OPERATION") : 0;
	(err == -60) ? get_error("CL_INVALID_GL_OBJECT") : 0;
	(err == -61) ? get_error("CL_INVALID_BUFFER_SIZE") : 0;
	(err == -62) ? get_error("CL_INVALID_MIP_LEVEL") : 0;
	(err == -63) ? get_error("CL_INVALID_GLOBAL_WORK_SIZE") : 0;
	(err == -64) ? get_error("CL_INVALID_PROPERTY") : 0;
	(err == -65) ? get_error("CL_INVALID_IMAGE_DESCRIPTOR") : 0;
	(err == -66) ? get_error("CL_INVALID_COMPILER_OPTIONS") : 0;
	(err == -67) ? get_error("CL_INVALID_LINKER_OPTIONS") : 0;
	(err == -68) ? get_error("CL_INVALID_DEVICE_PARTITION_COUNT") : 0;
	return (ocl_get_error_string2(err));
}

/*
**		run-time and JIT compiler errors
**			extension errors
*/

const char			*ocl_get_error_string(int err)
{
	const char *msg;

	msg = ocl_get_error_string1(err);
	if (msg)
		return (msg);
	(err == -1000) ? get_error("CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR") : 0;
	(err == -1001) ? get_error("CL_PLATFORM_NOT_FOUND_KHR") : 0;
	(err == -1002) ? get_error("CL_INVALID_D3D10_DEVICE_KHR") : 0;
	(err == -1003) ? get_error("CL_INVALID_D3D10_RESOURCE_KHR") : 0;
	(err == -1004) ? get_error("CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR") : 0;
	(err == -1005) ? get_error("CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR") : 0;
	ft_putnbr(err);
	ft_putstr(" OpenCL Error\n");
	return ("Unknown OpenCL err");
}

/*
** const char				*ocl_get_error_string(int error)
** {
** 	(void)error;
** 	return ("Unknown OpenCL error");
** }
*/

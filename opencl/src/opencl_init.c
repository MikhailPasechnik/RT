#include "opencl_defs.h"

cl_device_id	opencl_create_device()
{
	cl_platform_id	platform_id;
	cl_device_id	device_id;
	cl_int			err;

	err = clGetPlatformIDs(1, &platform_id, NULL);
	if (err != CL_SUCCESS)
	{
		perror("opencl: Couldn't identify a platform");
		return (NULL);
	}
	err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);
	if (err != CL_SUCCESS)
		err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 1, &device_id, NULL);
	if (err != CL_SUCCESS)
	{
		perror("opencl: No suitable device found");
		return (NULL);
	}
	return (device_id);
}

int		opencl_init(t_cl *cl,
   void (*pfn_notifu)(
   		const char *errinfo, const void *private_info, size_t cb, void *user_data
   )
)
{
	cl_int	err;
	if (!(cl->device = opencl_create_device()))
		return (0);
	cl->context = clCreateContext(NULL, 1, &cl->device, pfn_notifu, NULL, &err);
	if (err != CL_SUCCESS)
	{
		clReleaseDevice(cl->device);
		cl->device = NULL;
		perror("opencl: Failed to create context");
		return (0);
	}
	cl->queue = clCreateCommandQueueWithProperties(cl->context, cl->device, NULL, &err);
	if (err != CL_SUCCESS)
	{
		clReleaseDevice(cl->device);
		clReleaseContext(cl->context);
		cl->device = NULL;
		cl->context = NULL;
		perror("opencl: Failed to create queue");
		return (0);
	}
	return (1);
}


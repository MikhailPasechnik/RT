#include "opencl_defs.h"

void	opencl_simple_notify(
		const char *errinfo, const void *private_info,
		size_t cb, void *user_data)
{
	errinfo ? ft_putendl(errinfo) : 0;
	(void)private_info;
	(void)cb;
	(void)user_data;
}

void	opencl_release(t_cl *cl)
{
	if (cl->queue)
		clReleaseCommandQueue(cl->queue);
	if (cl->context)
		clReleaseContext(cl->context);
}

char	*opencl_get_build_log(cl_program program, cl_device_id device_id)
{
	size_t	size;
	char 	*log;

	clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &size);
	if ((log = ft_strnew(size)) == NULL)
		return (NULL);
	clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, log, NULL);
	return (log);
}

void	opencl_log_program_build(cl_program program, cl_device_id device_id)
{
	char *log;

	log = opencl_get_build_log(program, device_id);
	if (log)
	{
		ft_putendl(log);
		ft_strdel(&log);
	}
}

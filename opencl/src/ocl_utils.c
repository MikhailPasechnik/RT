#include "ocl.h"

void	ocl_release(t_ocl *cl)
{
	if (cl->queue)
		clReleaseCommandQueue(cl->queue);
	if (cl->context)
		clReleaseContext(cl->context);
}

char	*ocl_get_build_log(cl_program program, cl_device_id device_id)
{
	size_t	size;
	char 	*log;

	clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &size);
	if ((log = ft_strnew(size)) == NULL)
		return (NULL);
	clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, log, NULL);
	return (log);
}

void	ocl_log_program_build(cl_program program, cl_device_id device_id)
{
	char *log;

	log = ocl_get_build_log(program, device_id);
	if (log)
	{
		ft_putendl(log);
		ft_strdel(&log);
	}
}

void	ocl_put_error(int err, const char *msg, const char *file, int line)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(" ", 2);
	ft_putendl_fd(ocl_get_error_string(err), 2);
}

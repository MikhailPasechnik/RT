#ifndef OPENCL_H
# define OPENCL_H

#ifdef __APPLE__
	# include <OpenCL/opencl.h>
#else
	# include <CL/opencl.h>
#endif
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"

cl_device_id	opencl_create_device();
cl_program		opencl_compile_program(cl_context ctx, cl_device_id device_id,
		const char *file_name, int build_log);

typedef struct	s_cl
{
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	queue;
}				t_cl;

int				opencl_init(t_cl *cl,
   void (*pfn_notifu)(
		   const char *errinfo, const void *private_info,
		   size_t cb, void *user_data)
);
void			opencl_release(t_cl *cl);
void			opencl_simple_notify(
		const char *errinfo, const void *private_info,
		size_t cb, void *user_data);
char			*opencl_get_build_log(cl_program program, cl_device_id device_id);
void			opencl_log_program_build(cl_program program, cl_device_id device_id);
const char		*opencl_get_error_string(cl_int error);

#endif

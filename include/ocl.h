#ifndef OCL_H
# define OCL_H

#ifdef __APPLE__
	# include <OpenCL/opencl.h>
#else
	# include <CL/opencl.h>
#endif

# include <fcntl.h>
# include <errno.h>

# include "libft.h"

cl_device_id	ocl_create_device();
cl_program		ocl_compile_program(cl_context ctx, cl_device_id device_id,
	  	const char *file_name, int build_log);

typedef struct	s_cl
{
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	queue;
}				t_ocl;

int				ocl_init(t_ocl *cl);
void			ocl_release(t_ocl *cl);
char			*ocl_get_build_log(cl_program program, cl_device_id device_id);
void			ocl_log_program_build(cl_program program, cl_device_id device_id);
const char		*ocl_get_error_string(cl_int error);

int				ocl_put_error(int err, const char *msg,
		const char *file, int line);

# define OCL_PUT_ERROR(err, msg)(ocl_put_error(err, msg, __FILE__, __LINE__))
# define OCL_ERROR(err, msg)(err != CL_SUCCESS ?  OCL_PUT_ERROR(err, msg): 0)
# define OCL_ERROR2(err)(err != CL_SUCCESS ?  OCL_PUT_ERROR(err, NULL): 0)

#endif

#include "ocl.h"

static int 		open_file_fd(const char *file_name)
{
	int		fd;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (0);
	if (read(fd, NULL, 0) != 0)
	{
		close(fd);
		return (0);
	}
	return (fd);
}

static char 	*read_file(const char *file_name)
{
	int		fd;
	int		rd;
	char 	buff[1024 + 1];
	char 	*res;
	char 	*tmp;

	if (!(fd = open_file_fd(file_name)))
	{
		ft_putendl_fd("Failed to read file", 2);
		return (NULL);
	}
	if ((res = ft_strnew(0)) == NULL)
	{
		close(fd);
		return (NULL);
	}
	while ((rd = read(fd, buff, 1024)))
	{
		buff[rd] = '\0';
		tmp = ft_strjoin(res, buff);
		ft_strdel(&res);
		if ((res = tmp) == NULL)
		{
			close(fd);
			return (NULL);
		}
	}
	close(fd);
	return (res);
}

cl_program		ocl_compile_program(cl_context ctx, cl_device_id device_id,
									  const char *file_name, int build_log)
{
	cl_program	program;
	char 		*buff;
	char 		*log;
	cl_int		err;
	size_t 		size;

	if (!(buff = read_file(file_name)))
		return (NULL);
	size = ft_strlen(buff);
	program = clCreateProgramWithSource(ctx, 1, (const char **)&buff, &size, &err);
	ft_strdel(&buff);
	if (OCL_ERROR(err, "Couldn't create the program"))
		return (NULL);
	err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (OCL_ERROR(err, "Failed to build program"))
	{
		(log = ocl_get_build_log(program, device_id)) ? ft_putendl_fd(log, 2) : 0;
		log ? ft_strdel(&log): 0;
		return (NULL);
	}
	build_log ? ocl_log_program_build(program, device_id) : 0;
	return (program);
}

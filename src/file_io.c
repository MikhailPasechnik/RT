/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:50:25 by bmahi             #+#    #+#             */
/*   Updated: 2020/02/16 16:07:56 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/file_io.h"

int			fio_open_fd(const char *file_name)
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

char		*fio_read_file(const char *file_name, size_t *size)
{
	int		fd;
	int		rd;
	char	buff[1024 + 1];
	char	*str;
	char	*joined;

	if (!(fd = fio_open_fd(file_name)))
		return (NULL);
	if (size)
		*size = 0;
	str = NULL;
	while ((rd = read(fd, buff, 1024)))
	{
		if (size)
			*size += rd;
		buff[rd] = '\0';
		joined = ft_strjoin(str ? str : "", buff);
		if (str)
			ft_strdel(&str);
		if ((str = joined) == NULL)
			break ;
	}
	close(fd);
	return (str);
}

int			fio_read_files(const char **file_names, size_t count,
			char ***content, size_t **size)
{
	size_t	i;

	if (!(*content = malloc(sizeof(**content) * count)) ||
		!(*size = malloc(sizeof(**size) * count)))
	{
		*content ? free(*content) : 0;
		return 0;
	}
	i = 0;
	while (i < count)
	{
		if (((*content)[i] = fio_read_file(file_names[i], &(*size)[i])) == NULL)
		{
			ft_putstr_fd("Failed to read file: ", 2);
			ft_putendl_fd(file_names[i], 2);
			while(i--)
				free((*content)[i]);
			free(*content);
			free(*size);
			break ;
		}
		i++;
	}
	return (i == count);
}

int			save_image(const char *file_name,
		unsigned int *data, size_t w, size_t h)
{
	int		fd;
	size_t	y;
	size_t	i;
	char	name[FILENAME_MAX];

	if (ft_strlen(file_name) + 4 > FILENAME_MAX)
		return (0);
	ft_sprintf(name, "%s.pgm", file_name);
	if ((fd = open(name, O_RDWR | O_CREAT, 0666)) == -1)
		return  (0);
	i = 0;
	ft_fprintf(fd, "P3\n%zu %zu\n255", w, h);
	while (i < w * h)
	{
		y = i % w;
		!y ? write(fd, "\n", 1) : 0;
		ft_fprintf(fd, "%u %u %u ",
				data[i] >> 16u & 0xFFu, data[i] >> 8u & 0xFFu, data[i] & 0xFFu);
		i++;
	}
	write(fd, "\n", 1);
	close(fd);
	return (1);
}
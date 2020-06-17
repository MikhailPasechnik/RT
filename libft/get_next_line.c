/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktgri <ktgri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 14:41:19 by bmahi             #+#    #+#             */
/*   Updated: 2020/06/16 15:20:51 by ktgri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
# define BUFF_SIZE 30
# ifndef OPEN_MAX
  # define OPEN_MAX 64
# endif

static int	gnl_read_line(int fd, int ret, char **s, char **line)
{
	char	*tmp;
	int		len;

	len = 0;
	while (s[fd][len] != '\n' && s[fd][len] != '\0')
		len++;
	if (s[fd][len] == '\n')
	{
		*line = ft_strsub(s[fd], 0, len);
		tmp = ft_strdup(s[fd] + len + 1);
		free(s[fd]);
		s[fd] = tmp;
		if (s[fd][0] == '\0')
			ft_strdel(&s[fd]);
	}
	else if (s[fd][len] == '\0')
	{
		if (ret == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(s[fd]);
		ft_strdel(&s[fd]);
	}
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	int			ret_value;
        static char	*s[OPEN_MAX];
	char		buf[BUFF_SIZE + 1];
	char		*tmp;

	if ((fd < 0 || fd >= OPEN_MAX) || !line || (read(fd, s[fd], 0) < 0))
		return (-1);
	while ((ret_value = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret_value] = '\0';
		if (!s[fd])
			s[fd] = ft_strnew(1);
		tmp = ft_strjoin(s[fd], buf);
		free(s[fd]);
		s[fd] = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret_value < 0)
		return (-1);
	else if (!ret_value && (!s[fd] || s[fd][0] == '\0'))
		return (0);
	return (gnl_read_line(fd, ret_value, s, line));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 14:41:19 by bmahi             #+#    #+#             */
/*   Updated: 2020/02/29 00:02:37 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
# ifndef OPEN_MAX
# define OPEN_MAX 265
# endif

# define BUFF_SIZE 30

static int	gnl_check_line(char **s, char **line)
{
	int		i;
	char	*stack;
	char	*tmp_stack;

	i = 0;
	stack = *s;
	while (stack[i] != '\n')
		if (!stack[i++])
			return (0);
	tmp_stack = &stack[i];
	*tmp_stack = '\0';
	*line = ft_strdup(*s);
	*s = ft_strdup(tmp_stack + 1);
	free(stack);
	return (1);
}

static int	gnl_read_fd(int fd, char *pec, char **s, char **line)
{
	int		ret_value;
	char	*tmp_stack;

	while ((ret_value = read(fd, pec, BUFF_SIZE)) > 0)
	{
		pec[ret_value] = '\0';
		if (*s)
		{
			tmp_stack = *s;
			*s = ft_strjoin(tmp_stack, pec);
			free(tmp_stack);
			tmp_stack = NULL;
		}
		else
			*s = ft_strdup(pec);
		if (gnl_check_line(s, line))
			break ;
	}
	if (ret_value > 0)
		return (1);
	return (ret_value);
}

int			get_next_line(const int fd, char **line)
{
	int			i;
	int			ret_value;
	char		*pec;
	static char	*s[OPEN_MAX];

	i = 0;
	pec = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!line || (fd < 0 || fd >= OPEN_MAX) || (read(fd, s[fd], 0) < 0) || !pec)
		return (-1);
	if (s[fd])
		if (gnl_check_line(&s[fd], line))
			return (1);
	while (i < BUFF_SIZE)
		pec[i++] = '\0';
	ret_value = gnl_read_fd(fd, pec, &s[fd], line);
	free(pec);
	if (ret_value != 0 || s[fd] == NULL || s[fd][0] == '\0')
	{
		if (!ret_value && *line)
			*line = NULL;
		return (ret_value);
	}
	*line = s[fd];
	s[fd] = NULL;
	return (1);
}
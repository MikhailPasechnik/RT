/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:17:58 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:55:54 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_iswhitespace_cmp(int c)
{
	return (!ft_iswhitespace(c));
}

char			*ft_strtrim(char const *s)
{
	size_t	len;
	size_t	start;
	size_t	end;
	char	*new;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	end = ft_count_till(s, -1, len - 1, ft_iswhitespace_cmp);
	start = ft_count_till(s, 1, 0, ft_iswhitespace_cmp);
	if (start >= len - end)
		return (ft_strnew(0));
	else if ((new = ft_strnew(len - start - end)) == NULL)
		return (NULL);
	ft_strncpy(new, &s[start], len - start - end);
	new[len - start - end] = '\0';
	return (new);
}

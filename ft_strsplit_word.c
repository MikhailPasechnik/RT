/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:17:16 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 10:43:10 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_count(const char *str, const char *dl)
{
	size_t		count;
	size_t		len;

	if (!str || !dl)
		return (0);
	len = ft_strlen(dl);
	str += ft_strnequ(str, dl, len) ? len : 0;
	count = 0;
	while (*str != '\0')
	{
		str = ft_strstr(str, dl);
		if (!str)
			return (++count);
		count++;
		str += len;
	}
	return (count);
}

char			**ft_strsplit_word(char const *s, char *w)
{
	size_t		count;
	char		**res;
	size_t		i;
	size_t		len;
	const char	*end;

	count = ft_word_count(s, w);
	if (!s || !w || (res = malloc(sizeof(*res) * (count + 1))) == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(w);
	s += ft_strnequ(s, w, len) ? len : 0;
	while (i < count)
	{
		end = strstr(s, w);
		end = end ? end : s + ft_strlen(s);
		if ((res[i] = ft_strnew(end - s)) == NULL)
			return (NULL);
		ft_strncpy(res[i], s, end - s);
		res[i][end - s] = '\0';
		s = end + len;
		i++;
	}
	res[i] = NULL;
	return (res);
}

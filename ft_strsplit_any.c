/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_ext.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:17:16 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:17:20 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

static size_t	ft_count(const char *s, const char *c,
						  int ref, int (*cmp)(const char *a, char b))
{
	size_t	count;

	count = 0;
	while (s[count] && cmp(c, s[count]) == ref)
		count++;
	return (count);
}

static int		ft_any_match(const char *s, const char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

static size_t	ft_word_count(const char *str, const char *dl)
{
	size_t	count;

	count = 0;
	while (str && dl && *str != '\0')
	{
		str += ft_count(str, dl, 1, ft_any_match);
		if (!*str)
			return (count);
		str += ft_count(str, dl, 0, ft_any_match) ;
		count++;
	}
	return (count);
}

char 			**ft_strsplit_any(char const *s, char *c)
{
	size_t		size;
	char		**res;
	size_t		till_del;
	size_t		i;

	size = ft_word_count(s, c);
	if (!s || !c || (res = malloc(sizeof(*res) * (size + 1))) == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		s += ft_count(s, c, 1, ft_any_match);
		till_del = ft_count(s, c, 0, ft_any_match);
		if ((res[i] = ft_strnew(till_del)) == NULL)
			return (NULL);
		ft_strncpy(res[i], s, till_del);
		res[i][till_del] = '\0';
		s+=till_del;
		i++;
	}
	res[i] = NULL;
	return (res);
}

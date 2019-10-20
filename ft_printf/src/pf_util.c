/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caellis <caellis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 18:56:52 by bnesoi            #+#    #+#             */
/*   Updated: 2019/08/20 10:52:34 by caellis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t		pf_u_power(uintmax_t nb, int p)
{
	if (p < 0)
		return (0);
	if (p == 0)
		return (1);
	return (nb * pf_u_power(nb, p - 1));
}

int				pf_in(const char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

size_t			pf_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

void			pf_bzero(void *s, size_t n)
{
	char	*v;

	v = s;
	while (n--)
		*v++ = '\0';
}

char			*pf_strcpy(char *dst, const char *src)
{
	char *res;

	res = dst;
	while (*src)
		*dst++ = *src++;
	*dst = *src;
	return (res);
}

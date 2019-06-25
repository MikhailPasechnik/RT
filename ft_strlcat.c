/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 21:49:15 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:14:18 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	const char	*s;
	char		*d;
	size_t		clen;
	size_t		dlen;

	clen = size;
	d = dest;
	s = src;
	while (--clen && *d)
		d++;
	dlen = d - dest;
	clen = size - dlen;
	while (*s)
	{
		if (clen > 1)
		{
			*d++ = *s;
			clen--;
		}
		s++;
	}
	*d = '\0';
	return(dlen + (s - src));
}

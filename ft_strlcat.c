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
	char		*d;
	const char	*s;
	size_t		n;
	size_t		ldest;

	n = size;
	d = dest;
	s = src;
	while (n-- && *d)
		d++;
	ldest = d - dest;
	n = size - ldest;
	if (n == 0)
		return(ldest + ft_strlen(s));
	while (*s && n-- != 1)
		*d++ = *s++;
	*d = '\0';
	return(ldest + ft_strlen(src));
}

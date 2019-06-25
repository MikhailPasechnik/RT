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
	size_t lsrc;
	size_t ldest;
	size_t i;

	lsrc = ft_strlen(src);
	i = size;
	ldest = 0;
	while (--i && dest[ldest])
		ldest++;
	if (ldest == size)
		return size + lsrc;
	if (lsrc < size - ldest)
	{
		ft_memcpy(dest + ldest, src, lsrc + 1);
	}
	else
	{
		ft_memcpy(dest + ldest, src, size - 1);
		dest[ldest + size - 1] = '\0';
	}
	return ldest + lsrc;
}

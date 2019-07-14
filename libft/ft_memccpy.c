/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:38:43 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:51:28 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char			*v_dest;
	const unsigned char		*v_src;
	unsigned char			v_c;
	size_t					i;

	v_dest = dest;
	v_src = src;
	v_c = c;
	i = 0;
	while (i < n)
	{
		v_dest[i] = v_src[i];
		if (v_src[i] == v_c)
			return (&v_dest[i + 1]);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:11:05 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:51:34 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char		*v_s;
	unsigned char			v_c;
	size_t					i;

	v_s = s;
	v_c = c;
	i = 0;
	while (i < n)
	{
		if (v_s[i] == v_c)
			return ((void *)&v_s[i]);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:14:46 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:51:41 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*v1;
	const unsigned char	*v2;

	v1 = s1;
	v2 = s2;
	while (n--)
	{
		if (*v1 != *v2)
			return (*v1 - *v2);
		v1++;
		v2++;
	}
	return (0);
}

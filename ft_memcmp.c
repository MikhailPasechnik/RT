/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:14:46 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/06 16:18:02 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*v1;
	const unsigned char	*v2;
	size_t				i;

	v1 = s1;
	v2 = s2;
	i = 0;
	while (i < n && v1[i] == v2[i])
		i++;
	return (v1[i] - v2[i]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_till.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:35:29 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:55:52 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_till(const char *str, int dir, size_t start,
						int (*cmp)(int))
{
	size_t	count;

	if (!(dir == 1 || dir == -1))
		return (0);
	count = 0;
	while ((dir == 1 ? (unsigned char)str[start] : start) &&
		cmp(str[start]) == 0)
	{
		start += dir;
		count++;
	}
	return (count);
}

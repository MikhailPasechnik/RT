/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strhash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:05:44 by bnesoi            #+#    #+#             */
/*   Updated: 2019/05/08 20:03:07 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strhash(const char *s, size_t size)
{
	size_t	hash;
	size_t	i;

	i = 0;
	hash = 0;
	while (s && s[i])
	{
		hash = (hash + s[i]) % size;
		i++;
	}
	return (hash);
}

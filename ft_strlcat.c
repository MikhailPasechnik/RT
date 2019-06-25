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
	size_t	src_len;
	size_t	dest_len;
	size_t	left_len;
	size_t	cpy_len;

	src_len = ft_strlen(src);
	left_len = size;
	dest_len = 0;
	while (*dest && left_len > 0)
	{
		dest++;
		left_len--;
		dest_len++;
	}
	if (dest_len < left_len)
	{
		cpy_len = src_len < left_len - 1 ? src_len : left_len - 1;
		ft_memmove(dest, src, cpy_len);
		dest[cpy_len] = '\0';
	}
	return (src_len + dest_len);
}

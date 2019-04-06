/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 21:33:39 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/06 17:16:54 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *dst_copy;

	dst_copy = dst;
	while (*src && len-- != 0)
		*dst++ = *src++;
	while (len-- != 0)
		*dst++ = '\0';
	return (dst_copy);
}

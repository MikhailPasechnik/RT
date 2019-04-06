/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:08:22 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/06 17:15:33 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*start;
	size_t		sub;

	while (*haystack)
	{
		start = haystack;
		sub = 0;
		while (*haystack && needle[sub] && *haystack == needle[sub])
		{
			haystack++;
			sub++;
		}
		if (sub == len)
			return ((char *)start);
		haystack = start + 1;
	}
	return (NULL);
}

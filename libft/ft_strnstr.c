/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:08:22 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:17:00 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*start;
	size_t		j;
	size_t		i;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (*haystack && i < len)
	{
		start = haystack;
		j = 0;
		while (i + j < len && *haystack && needle[j] && *haystack == needle[j])
		{
			haystack++;
			j++;
		}
		if (!needle[j])
			return ((char *)start);
		haystack = start + 1;
		i++;
	}
	return (NULL);
}

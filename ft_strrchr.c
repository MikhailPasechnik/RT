/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:58:13 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/06 17:17:12 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	v;
	size_t	len;

	v = c;
	len = ft_strlen(s);
	if (!v)
		return ((char *)&s[len]);
	while (len--)
	{
		if (s[len] == v)
			return ((char *)&s[len]);
	}
	return (NULL);
}

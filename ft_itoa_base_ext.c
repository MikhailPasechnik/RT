/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_ext.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:47:56 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:48:31 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define TO_CHAR(n)(((n) > 9 ? (n) + 55 : (n) + '0'))

static char		*ft_itoa_set(char *dest, int n, int base)
{
	if (!n)
		return (dest);
	dest = ft_itoa_set(dest, n / base, base);
	*dest = n > 0 ? TO_CHAR(n % base) : TO_CHAR(-(n % base));
	return (dest + 1);
}

char			*ft_itoa_base_ext(char *dest, int n, int base, int sign)
{
	char	*end;

	if (!dest || base < 2 || base > 16)
		return (NULL);
	if (!n)
	{
		*dest = '0';
		end = dest + 1;
	}
	else
	{
		*dest = '-';
		end = ft_itoa_set(dest + (sign && n < 0), n, base);
	}
	*end = '\0';
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 21:48:14 by bnesoi            #+#    #+#             */
/*   Updated: 2019/03/05 22:09:21 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcapitalize(char *str)
{
	int i;

	str[0] = str[0] - (32 * FT_ISLOWER(str[0]));
	i = 1;
	while (str[i] != '\0')
	{
		if (FT_ISLOWER(str[i]))
		{
			if (!(FT_ISLOWER(str[i - 1])) &&
				!(FT_ISUPPER(str[i - 1])) &&
				!(ft_isdigit(str[i - 1])))
			{
				str[i] = str[i] - 32;
			}
		}
		else if ((FT_ISLOWER(str[i - 1])) ||
                 (FT_ISUPPER(str[i - 1])) ||
                 (ft_isdigit(str[i - 1])))
		{
			str[i] = str[i] + (32 * FT_ISUPPER(str[i]));
		}
		i++;
	}
	return (str);
}

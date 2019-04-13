/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:48:36 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:48:56 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(int n, int base)
{
	size_t	len;
	int		tmp;
	char	*dest;

	if (base < 2 || base > 16)
		return (NULL);
	len = n > 0 ? 0 : 1;
	tmp = n;
	while (tmp)
	{
		tmp /= base;
		++len;
	}
	if ((dest = ft_strnew(len)) == NULL)
		return (NULL);
	return (ft_itoa_base_ext(dest, n, base, base == 10));
}

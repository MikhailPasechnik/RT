/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tap_ismem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 09:58:04 by bnesoi            #+#    #+#             */
/*   Updated: 2019/05/11 15:28:20 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tap_ismem(t_plc place, const char *a, const char *b, size_t n)
{
	size_t	i;

	i = 0;
	while (i++ < n)
	{
		if (*a != *b)
		{
			ft_putstr("KO\n#   Failed test at ");
			ft_putstr(place.file);
			ft_putstr(":");
			ft_putnbr(place.line);
			ft_putstr("\n#      diff at: a[");
			ft_putnbr(i - 1);
			ft_putstr("]\n");
			return ;
		}
		a++;
		b++;
	}
	ft_putstr("OK\n");
}

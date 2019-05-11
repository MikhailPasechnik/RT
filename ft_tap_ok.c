/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tap_ok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 09:56:16 by bnesoi            #+#    #+#             */
/*   Updated: 2019/05/11 15:28:29 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tap_ok(t_plc place, int a)
{
	if (!a)
	{
		ft_putstr("KO\n#   Failed test at ");
		ft_putstr(place.file);
		ft_putstr(":");
		ft_putnbr(place.line);
		ft_putstr("\n");
	}
	else
		ft_putstr("OK\n");
}

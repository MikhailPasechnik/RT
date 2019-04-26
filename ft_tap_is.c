/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tap_is.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 09:56:53 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 09:57:06 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tap_is(t_plc place, const char *a, const char *b)
{
	if (ft_strcmp(a, b))
	{
		ft_putstr("KO\n#   Failed test ");
		ft_putstr(place.file);
		ft_putstr(" line ");
		ft_putnbr(place.line);
		ft_putstr("\n#          got: '");
		ft_putstr(a);
		ft_putstr("'\n#     expected: '");
		ft_putstr(b);
		ft_putstr("'\n");
	}
	else
		ft_putstr("OK\n");
}

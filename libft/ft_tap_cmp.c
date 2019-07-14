/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tap_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 09:59:43 by bnesoi            #+#    #+#             */
/*   Updated: 2019/05/11 15:28:04 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_print_fail(t_plc place, int a, int b, char *cmp)
{
	ft_putstr("KO\n#   Failed test ");
	ft_putstr(place.file);
	ft_putstr(":");
	ft_putnbr(place.line);
	ft_putstr("\n#            a: ");
	ft_putnbr(a);
	ft_putstr("\n#  ");
	ft_putstr(cmp);
	ft_putstr("\n#            d: ");
	ft_putnbr(b);
	ft_putstr("\n");
}

void			ft_tap_cmp(t_plc place, int a, int b, char *cmp)
{
	int		ok;

	ok = 0;
	if (ft_strcmp(cmp, "==") == 0)
		ok = a == b;
	else if (ft_strcmp(cmp, "<") == 0)
		ok = a < b;
	else if (ft_strcmp(cmp, ">") == 0)
		ok = a > b;
	else if (ft_strcmp(cmp, "<=") == 0)
		ok = a <= b;
	else if (ft_strcmp(cmp, ">=") == 0)
		ok = a >= b;
	else if (ft_strcmp(cmp, "!=") == 0)
		ok = a != b;
	if (!ok)
	{
		ft_print_fail(place, a, b, cmp);
		return ;
	}
	ft_putstr("OK\n");
}

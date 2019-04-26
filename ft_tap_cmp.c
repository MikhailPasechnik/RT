/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tap_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 09:59:43 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/24 09:59:44 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_print_fail(t_tap_fl fl, int a, int b, char *cmp)
{
	ft_putstr("KO\n#   Failed test ");
	ft_putstr(fl.file);
	ft_putstr(" line ");
	ft_putnbr(fl.line);
	ft_putstr("\n#            a: ");
	ft_putnbr(a);
	ft_putstr("\n#  ");
	ft_putstr(cmp);
	ft_putstr("\n#            d: ");
	ft_putnbr(b);
	ft_putstr("\n");
}

void			ft_tap_cmp(t_tap_fl fl, int a, int b, char *cmp)
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
		ft_print_fail(fl, a, b, cmp);
		return ;
	}
	ft_putstr("OK\n");
}

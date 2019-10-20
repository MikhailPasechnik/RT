/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_util_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caellis <caellis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 18:56:52 by bnesoi            #+#    #+#             */
/*   Updated: 2019/09/05 12:31:28 by caellis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int16_t			pf_u_exp_power(int16_t nb, int p)
{
	if (p < 0)
		return (pf_u_exp_power(1 / nb, -p));
	else if (p == 0)
		return (1);
	else if (p == 1)
		return (nb);
	else if (p % 2 == 0)
		return (pf_u_exp_power(nb * nb, p / 2));
	else
		return (nb * pf_u_exp_power(nb * nb, (p - 1) / 2));
}

void			pf_fast_bzero(void *s, size_t n)
{
	uint64_t	*v;

	v = s;
	n /= sizeof(uint64_t);
	while (n--)
		*v++ = 0;
}

int				is_not_realnum(t_real *real, t_pf_format *f)
{
	int			flag;

	if ((flag = (real->r_num.bits.exp == PF_D_EXP_E)))
	{
		if (real->r_num.bits.man)
			pf_put_buffered("nan", f, 3, 0);
		else if (real->r_num.bits.sign)
			pf_put_buffered("-inf", f, 4, 0);
		else
			pf_put_buffered("+inf", f, 4, 0);
	}
	return (flag);
}

int16_t			pf_lm_checktrailing(uint16_t longn[], int16_t pos)
{
	while (pos-- >= 1)
	{
		if (longn[pos] && (pos = -1))
			break ;
	}
	return (pos);
}

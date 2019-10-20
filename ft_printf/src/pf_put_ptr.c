/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_put_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caellis <caellis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 18:48:00 by bnesoi            #+#    #+#             */
/*   Updated: 2019/09/02 13:07:33 by caellis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		put_uint(uintmax_t n, t_pf_format *f, int base)
{
	char		c;
	uintmax_t	p;
	uintmax_t	i;
	int			len;

	p = 1;
	i = n;
	len = 0;
	while ((i /= base) && ++len)
		p *= base;
	pf_put_int_prefix(0, n == 0, f->prc > len ? f->prc - 1 : len, f);
	if (!n && !f->prc && f->flg & PF_F_PRC)
		return (pf_put_pad(f));
	while (--f->prc > len)
		pf_put_buffered("0", f, 1, 0);
	i = 1;
	while (42)
	{
		c = PF_BASE[((n / (p / i)) % base)];
		pf_put_buffered(&c, f, 1, 0);
		if (i == p)
			return (pf_put_pad(f));
		i *= base;
	}
}

/*
** Prints pointer.
** Special case of hex number
*/

void			pf_put_ptr(t_pf_format *f)
{
	uintptr_t	p;

	p = va_arg(f->va_args, uintptr_t);
	put_uint(p, f, 16);
}

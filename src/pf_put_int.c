/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_put_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caellis <caellis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 18:48:48 by bnesoi            #+#    #+#             */
/*   Updated: 2019/08/07 13:21:32 by caellis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			put_int(intmax_t n, t_pf_format *f, int base)
{
	char			c;
	intmax_t		p;
	intmax_t		i;
	int				len;

	p = 1;
	i = n;
	len = 0;
	while ((i /= base) && ++len)
		p *= base;
	pf_put_int_prefix(n < 0, n == 0, f->prc > len ? f->prc - 1 : len, f);
	while (--f->prc > len)
		pf_put_buffered("0", f, 1, 0);
	i = 1;
	while (42)
	{
		c = PF_BASE[((n < 0) ? -1 : 1) * ((n / (p / i)) % base)];
		c = (char)(f->cv == 'X' ? PF_TO_UP(c) : c);
		pf_put_buffered(&c, f, 1, 0);
		if (i == p)
			return (pf_put_pad(f));
		i *= base;
	}
}

static void			put_uint(uintmax_t n, t_pf_format *f, int base)
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
	pf_put_int_prefix(0, n == 0, len, f);
	if (f->flg & PF_F_ALT && n && f->cv == 'o')
		f->prc--;
	while (--f->prc > len)
		pf_put_buffered("0", f, 1, 0);
	i = 1;
	while (42)
	{
		c = PF_BASE[((n / (p / i)) % base)];
		c = (char)(f->cv == 'X' ? PF_TO_UP(c) : c);
		pf_put_buffered(&c, f, 1, 0);
		if (i == p)
			return (pf_put_pad(f));
		i *= base;
	}
}

/*
** Get signed int from va args based of user flags and print it.
** NOTE: Match flags in order from bigger sizeof to smaller.
** 		 Same as original printf
*/

static void			put_signed(t_pf_format *f)
{
	intmax_t	n;
	int			base;

	if (f->flg & (PF_F_IMAX | PF_F_LLONG))
		n = f->flg & PF_F_IMAX ? va_arg(f->va_args, intmax_t) :
			va_arg(f->va_args, long long);
	else if (f->flg & (PF_F_SIZE | PF_F_LONG))
		n = f->flg & PF_F_SIZE ? va_arg(f->va_args, ssize_t) :
			va_arg(f->va_args, long);
	else if (f->flg & PF_F_SHORT || f->flg & PF_F_CHAR)
		n = f->flg & PF_F_SHORT ?
			(short)va_arg(f->va_args, int) :
			(char)va_arg(f->va_args, int);
	else
		n = va_arg(f->va_args, int);
	if (pf_in("oxX", f->cv))
		base = f->cv == 'o' ? 8 : 16;
	else
		base = 10;
	if (f->flg & PF_F_PRC && !f->prc && !n && ++f->pad)
	{
		pf_put_int_prefix(n < 0, n == 0, 0, f);
		return (pf_put_pad(f));
	}
	put_int(n, f, base);
}

/*
** Get unsigned int from va args based of user flags and print it.
** NOTE: Match flags in order from bigger sizeof to smaller.
** 		 Same as original printf
*/

static void			put_unsigned(t_pf_format *f)
{
	uintmax_t	n;
	int			base;

	if (f->flg & (PF_F_IMAX | PF_F_LLONG))
		n = f->flg & PF_F_IMAX ? va_arg(f->va_args, uintmax_t) :
			va_arg(f->va_args, unsigned long long);
	else if (f->flg & (PF_F_SIZE | PF_F_LONG))
		n = f->flg & PF_F_SIZE ? va_arg(f->va_args, size_t) :
			va_arg(f->va_args, unsigned long);
	else if (f->flg & PF_F_SHORT || f->flg & PF_F_CHAR)
		n = f->flg & PF_F_SHORT ?
			(unsigned short)va_arg(f->va_args, unsigned int) :
			(unsigned char)va_arg(f->va_args, unsigned int);
	else
		n = va_arg(f->va_args, unsigned int);
	if (pf_in("oxX", f->cv))
		base = f->cv == 'o' ? 8 : 16;
	else
		base = 10;
	if (n == 0 && f->flg & PF_F_PRC && !f->prc &&
		!(f->cv == 'o' && f->flg & PF_F_ALT) && ++f->pad)
		return (pf_put_pad(f));
	put_uint(n, f, base);
}

void				pf_put_int(t_pf_format *f)
{
	if (pf_in(PF_CUI, f->cv))
		put_unsigned(f);
	else
		put_signed(f);
}

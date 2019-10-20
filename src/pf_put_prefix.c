/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_put_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 18:56:52 by bnesoi            #+#    #+#             */
/*   Updated: 2019/07/28 18:56:53 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Prints [oxX] prefix.
** Special cases:
** 	1: If num is zero, do not print '0' '0[xX]' prefix.
*/

static void		put_oxp_prefix(int is_zero, t_pf_format *f)
{
	if (f->flg & PF_F_ALT && !is_zero && f->cv == 'o')
		pf_put_buffered("0", f, 1, 0);
	else if (f->flg & PF_F_ALT && !is_zero && (f->cv == 'x' || f->cv == 'X'))
		pf_put_buffered(f->cv == 'x' ? "0x" : "0X", f, 2, 0);
	else if (f->cv == 'p')
		pf_put_buffered("0x", f, 2, 0);
}

/*
** Prints general unsigned int prefix.
** NOTE: Consumes padding size.
*/

static void		put_uint_prefix(int is_neg, int is_zero,
		int len, t_pf_format *f)
{
	f->pad -= (f->flg & PF_F_ALT && !is_zero && f->cv == 'o' && len > f->prc);
	f->pad -= (f->flg & PF_F_ALT && !is_zero &&
			(f->cv == 'x' || f->cv == 'X')) * 2;
	f->pad -= (f->cv == 'p') * 2;
	len = f->prc > len ? f->prc - 1 : len;
	f->pad -= (((f->flg & (PF_F_PLUS | PF_F_SPACE))
				&& !is_neg) || is_neg) + len;
	if (f->pad_c == '0')
	{
		if (f->flg & PF_F_SPACE && !is_neg)
			pf_put_buffered(" ", f, 1, 0);
		put_oxp_prefix(is_zero, f);
		if (!(f->flg & PF_F_LEFTJ))
			pf_put_pad(f);
	}
	else
	{
		if (!(f->flg & PF_F_LEFTJ))
			pf_put_pad(f);
		if (f->flg & PF_F_SPACE && !is_neg)
			pf_put_buffered(" ", f, 1, 0);
		put_oxp_prefix(is_zero, f);
	}
}

/*
** Prints general int prefix.
** NOTE: Consumes padding size.
*/

static void		put_sint_prefix(int is_neg, int len, t_pf_format *f)
{
	len = f->prc > len ? f->prc - 1 : len;
	f->pad -= (((f->flg & (PF_F_PLUS | PF_F_SPACE))
			&& !is_neg) || is_neg) + len;
	if (f->pad_c == '0')
	{
		if (f->flg & PF_F_SPACE && !is_neg)
			pf_put_buffered(" ", f, 1, 0);
		else if ((f->flg & PF_F_PLUS && !is_neg) || is_neg)
			pf_put_buffered(is_neg ? "-" : "+", f, 1, 0);
		if (!(f->flg & PF_F_LEFTJ))
			pf_put_pad(f);
	}
	else
	{
		if (!(f->flg & PF_F_LEFTJ))
			pf_put_pad(f);
		if (f->flg & PF_F_SPACE && !is_neg)
			pf_put_buffered(" ", f, 1, 0);
		else if ((f->flg & PF_F_PLUS && !is_neg) || is_neg)
			pf_put_buffered(is_neg ? "-" : "+", f, 1, 0);
	}
}

void			pf_put_int_prefix(int is_neg, int is_zero,
	int len, t_pf_format *f)
{
	if (pf_in(PF_CUI, f->cv) || pf_in(PF_CP, f->cv))
		put_uint_prefix(is_neg, is_zero, len, f);
	else
		put_sint_prefix(is_neg, len, f);
}

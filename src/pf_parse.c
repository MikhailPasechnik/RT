/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caellis <caellis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 18:46:50 by bnesoi            #+#    #+#             */
/*   Updated: 2019/09/02 13:06:10 by caellis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Parses width flags, reade from argument if * given.
** TODO: Check negative precision
*/

static void		parse_width(t_pf_format *f)
{
	if (*f->fmt == '*' && f->fmt++)
		f->pad = va_arg(f->va_args, int);
	else if (PF_NUM(*f->fmt))
	{
		f->pad = pf_atoi(f->fmt);
		while (PF_NUM(*f->fmt))
			f->fmt++;
	}
	else if (*f->fmt == '.' && f->fmt++)
	{
		f->flg |= PF_F_PRC;
		if (*f->fmt == '*' && f->fmt++)
			f->prc = va_arg(f->va_args, int);
		else
		{
			f->prc = PF_NUM(*f->fmt) ? pf_atoi(f->fmt) : 0;
			while (PF_NUM(*f->fmt))
				f->fmt++;
		}
	}
}

static void		parse_length(t_pf_format *f)
{
	if (*f->fmt == 'h' && *f->fmt++)
	{
		*f->fmt == 'h' ? (f->flg |= PF_F_CHAR) : (f->flg |= PF_F_SHORT);
		f->fmt += *f->fmt == 'h';
	}
	else if (*f->fmt == 'l' && *f->fmt++)
	{
		*f->fmt == 'l' ? (f->flg |= PF_F_LLONG) : (f->flg |= PF_F_LONG);
		f->fmt += *f->fmt == 'l';
	}
	else if (*f->fmt == 'L' && *f->fmt++)
		f->flg |= PF_F_LONGD;
	else if (*f->fmt == 'j' && *f->fmt++)
		f->flg |= PF_F_IMAX;
	else if (*f->fmt == 'z' && *f->fmt++)
		f->flg |= PF_F_SIZE;
}

/*
** Called when all parsing done.
** Handles special cases:
**  : If padding is negative, abs it and set left justify flag.
**  : If precision is negative, ignore it.
** 	: If precision given by user and zero padding, remove zero flag
** 		as we use zero prefix for integers precision.
** 	: Remove signed flags if unsigned conversion.
** 	: Remove space flag if plus flag given, as for negative it will be consumed
** 		by minus sign and for positive with plus sign.
** 	: Set padding character to '0' for right prefix if flag zero present.
** 	: Set long flag for upper 'U' conversion.
*/

static void		post_parse(t_pf_format *f)
{
	if (f->pad < 0)
		(f->flg |= PF_F_LEFTJ) && (f->pad *= -1);
	if (f->prc < 0)
		!(f->prc *= 0) && (f->flg &= ~PF_F_PRC);
	if (pf_in(PF_CI, f->cv) && f->flg & PF_F_PRC)
	{
		f->flg &= ~PF_F_ZERO;
	}
	if (pf_in(PF_CUI, f->cv))
	{
		f->flg &= ~PF_F_SPACE;
		f->flg &= ~PF_F_PLUS;
	}
	if (f->flg & PF_F_PLUS)
		f->flg &= ~PF_F_SPACE;
	if (f->flg & PF_F_ZERO && !(f->flg & PF_F_LEFTJ))
		f->pad_c = '0';
	if (f->cv == 'U' || f->cv == 'D' || f->cv == 'O')
		f->flg |= PF_F_LONG;
}

static void		parse_flags(t_pf_format *f)
{
	while (pf_in(" #+-0", *f->fmt))
		if (*f->fmt == ' ' && *f->fmt++)
			f->flg |= PF_F_SPACE;
		else if (*f->fmt == '+' && *f->fmt++)
			f->flg |= PF_F_PLUS;
		else if (*f->fmt == '-' && *f->fmt++)
			f->flg |= PF_F_LEFTJ;
		else if (*f->fmt == '#' && *f->fmt++)
			f->flg |= PF_F_ALT;
		else if (*f->fmt == '0' && *f->fmt++)
			f->flg |= PF_F_ZERO;
		else if (*f->fmt == '\'' && *f->fmt++)
			f->flg |= PF_F_GROUP;
		else if (*f->fmt == 'I' && *f->fmt++)
			f->flg |= PF_F_I18N;
}

void			pf_parse_format(t_pf_format *f)
{
	f->prc = 0;
	f->flg = 0;
	f->pad_c = ' ';
	parse_flags(f);
	parse_width(f);
	parse_width(f);
	parse_flags(f);
	parse_length(f);
	f->cv = *f->fmt;
	f->error = !pf_in(PF_C, f->cv);
	post_parse(f);
}

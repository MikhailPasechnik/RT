/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_put_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caellis <caellis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 18:50:17 by bnesoi            #+#    #+#             */
/*   Updated: 2019/09/05 12:31:10 by caellis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static uint16_t		get_long_string(t_pf_real r, char *res, int prec, \
									unsigned int flg)
{
	int				i;
	int				len;

	pf_fast_bzero(res, sizeof(char) * PF_LM_MAXLEN);
	i = r.r_long_int[0];
	len = i;
	while (i)
		*(res++) = (char)(r.r_long_int[i--] + 48U);
	if ((prec || (flg & PF_F_ALT)) && len++)
		*(res++) = '.';
	i = r.r_long_frac[0];
	if (prec)
	{
		len += prec;
		while (prec--)
		{
			if (i >= 1)
				*res++ = (char)(r.r_long_frac[i--] + 48U);
			else
				*res++ = 48U;
		}
	}
	*++res = '\0';
	return (len);
}

static void			pf_lm_round(uint16_t l_int[], uint16_t l_frac[], \
						int prec, uint16_t buff[])
{
	int16_t			check;

	check = l_frac[0] - prec < 0 ? prec + 1 : l_frac[0] - prec;
	if (l_frac[check] >= 5 && (buff[check + 1] = 1))
	{
		if (l_frac[check] == 5)
			check = pf_lm_checktrailing(l_frac, check);
		if (check == -1 || l_frac[check] > 5)
		{
			if (!prec)
				pf_lm_add_one(l_int, 1);
			else
				pf_lm_add(l_frac, buff, 0);
		}
		else if (!prec && l_int[1] % 2 == 1)
			pf_lm_add_one(l_int, 1);
		else if (l_frac[l_frac[0] - prec] % 2 == 1)
			pf_lm_add(l_frac, buff, 0);
		if ((l_frac[0] = buff[0]) && l_frac[1 + l_frac[0]])
			pf_lm_add_one(l_int, 1);
	}
}

static uint8_t		get_longarrs(t_pf_real *r, uint16_t tmp[], uint8_t is_den)
{
	int64_t			i;

	i = 64;
	while (i--)
	{
		if ((r->r_num.bits.man >> i) & 1U)
		{
			tmp[0] = pf_lm_power(tmp, r->r_n_exp, is_den);
			if (r->r_n_exp >= 0)
				pf_lm_add(r->r_long_int, tmp, tmp[0]);
			else
				pf_lm_add(r->r_long_frac, tmp, tmp[0]);
			pf_fast_bzero(tmp, sizeof(uint16_t) * PF_LM_MAXLEN);
		}
		r->r_n_exp--;
	}
	tmp[0] = r->r_long_frac[0];
	return (r->r_n_exp == -16382);
}

static uint16_t		double_toa(t_pf_real *r, char *res, int prec, unsigned int flg)
{
	uint16_t		tmp[PF_LM_MAXLEN];
	uint8_t			is_denorm;

	pf_fast_bzero(tmp, sizeof(uint16_t) * PF_LM_MAXLEN);
	get_longarrs(r, tmp, is_denorm = (r->r_n_exp == -16382));
	pf_lm_round(r->r_long_int, r->r_long_frac, prec, tmp);
	if (is_denorm)
		r->r_long_frac[0] += prec + 1;
	return (get_long_string(*r, res, prec, flg));
}

void				pf_put_float(t_pf_format *f)
{
	char			res[PF_LM_MAXLEN];
	int				len;
	t_pf_real			real;

	pf_fast_bzero(real.r_long_int, sizeof(uint16_t) * PF_LM_MAXLEN);
	pf_fast_bzero(real.r_long_frac, sizeof(uint16_t) * PF_LM_MAXLEN);
	real.r_long_int[0] = 1;
	real.r_long_frac[0] = 1;
	f->prc = f->flg & PF_F_PRC ? f->prc : PF_D_PREC;
	if (f->flg & PF_F_LONGD)
		real.r_num.n = va_arg(f->va_args, long double);
	else
		real.r_num.n = (long double)va_arg(f->va_args, double);
	real.r_n_exp = !real.r_num.bits.exp ? -16382 : \
							(int16_t)(real.r_num.bits.exp - PF_D_EXP_BIAS);
	if (is_not_realnum(&real, f))
		return ;
	len = double_toa(&real, res, f->prc, f->flg);
	pf_put_int_prefix(real.r_num.bits.sign, !real.r_num.n, len - 1, f);
	pf_put_buffered(res, f, len, 0);
	pf_put_pad(f);
}

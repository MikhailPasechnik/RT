/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_long_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caellis <caellis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:26:12 by caellis           #+#    #+#             */
/*   Updated: 2019/09/05 12:19:25 by caellis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		pf_lm_shift_right(uint16_t long_n[], uint16_t shift)
{
	uint16_t	prev_len;

	prev_len = long_n[0];
	long_n[0] = shift;
	while (shift > 0 && prev_len)
		long_n[shift--] = long_n[prev_len--];
	while (shift > 0)
		long_n[shift--] = 0;
}

void			pf_lm_add(uint16_t long_a[], uint16_t long_b[], int16_t shift)
{
	uint16_t	i;
	uint16_t	c;

	i = 0;
	c = 0;
	if (shift > 1)
		pf_lm_shift_right(long_a, shift);
	while (++i < PF_LM_MAXLEN)
	{
		c += long_a[i] + long_b[i];
		if ((long_a[i] = c % PF_LM_BASE) && !shift)
			long_a[0] = i;
		c /= PF_LM_BASE;
	}
	if (shift)
		long_a[0] = (long_a[0] <= shift ? shift : long_a[0]);
}

static void		pf_lm_mul(uint16_t long_n[], uint16_t mul)
{
	uint16_t	i;
	uint16_t	c;

	i = 0;
	c = 0;
	while (mul > PF_LM_MAXMUL)
		pf_lm_mul(long_n, (mul = mul - PF_LM_MAXMUL));
	while (++i < PF_LM_MAXLEN)
	{
		c += long_n[i] * mul;
		if ((long_n[i] = c % PF_LM_BASE))
			long_n[0] = i;
		c /= PF_LM_BASE;
	}
}

int16_t			pf_lm_power(uint16_t result[], int16_t exp, uint8_t is_denorm)
{
	int16_t		neg_power_shift;

	result[1] = 1;
	neg_power_shift = 0;
	while (exp >= 12)
	{
		pf_lm_mul(result, PF_LM_2POW12);
		exp -= 12;
	}
	if (exp > 0)
		pf_lm_mul(result, pf_u_exp_power(2, exp));
	else if (exp < 0)
	{
		neg_power_shift = (is_denorm ? 0 : -exp);
		while (exp <= -5)
		{
			pf_lm_mul(result, PF_LM_5POW5);
			exp += 5;
		}
		if (exp < 0)
			pf_lm_mul(result, pf_u_exp_power(5, -exp));
	}
	return (neg_power_shift);
}

void			pf_lm_add_one(uint16_t long_a[], uint32_t pos)
{
	uint16_t	buff[PF_LM_MAXLEN];

	pf_fast_bzero(buff, sizeof(uint16_t) * PF_LM_MAXLEN);
	buff[0] = 1;
	buff[pos] = 1;
	pf_lm_add(long_a, buff, 0);
}

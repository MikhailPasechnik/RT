/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_put_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 18:48:00 by bnesoi            #+#    #+#             */
/*   Updated: 2019/07/28 18:48:27 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		put_padding(t_pf_format *f)
{
	while (--f->pad > 0)
		pf_put_buffered(&f->pad_c, f, 1, 0);
}

void			pf_put_char(t_pf_format *f)
{
	char	c;

	c = (char)va_arg(f->va_args, unsigned int);
	!(f->flg & PF_F_LEFTJ) ? put_padding(f) : 0;
	pf_put_buffered(&c, f, 1, 0);
	f->flg & PF_F_LEFTJ ? put_padding(f) : 0;
}

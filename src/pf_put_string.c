/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_put_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 18:55:52 by bnesoi            #+#    #+#             */
/*   Updated: 2019/07/28 18:56:12 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		put_padding(size_t len, t_pf_format *f)
{
	f->pad -= (int)len - 1;
	while (--f->pad > 0)
		pf_put_buffered(&f->pad_c, f, 1, 0);
}

void			pf_put_string(t_pf_format *f)
{
	char	*s;
	size_t	len;

	s = (char *)va_arg(f->va_args, char *);
	if (s == NULL)
		s = "(null)";
	len = pf_strlen(s);
	len = f->flg & PF_F_PRC && f->prc < (int)len ? (size_t)f->prc : len;
	!(f->flg & PF_F_LEFTJ) ? put_padding(len, f) : 0;
	pf_put_buffered(s, f, len, 0);
	f->flg & PF_F_LEFTJ ? put_padding(len, f) : 0;
}

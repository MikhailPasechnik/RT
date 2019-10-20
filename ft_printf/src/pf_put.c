/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 18:56:29 by bnesoi            #+#    #+#             */
/*   Updated: 2019/07/28 18:56:47 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			pf_put_pad(t_pf_format *f)
{
	while (--f->pad > 0)
		pf_put_buffered(&f->pad_c, f, 1, 0);
}

static void		put_switch(t_pf_format *f)
{
	if (pf_in(PF_CI, f->cv))
		pf_put_int(f);
	else if (pf_in(PF_CS, f->cv))
		pf_put_string(f);
	else if (pf_in(PF_CC, f->cv))
		pf_put_char(f);
	else if (pf_in(PF_CF, f->cv))
		pf_put_float(f);
	else if (pf_in(PF_CP, f->cv))
		pf_put_ptr(f);
	else if (f->cv == '%')
		pf_put_empty(f);
	else
		f->error = 1;
}

void			pf_put_format(t_pf_format *f)
{
	f->cv = 0;
	f->prc = 0;
	f->pad = 0;
	f->pad_c = 0;
	f->error = 0;
	pf_parse_format(f);
	!f->error ? put_switch(f) : 0;
	if (f->error)
		pf_put_buffered(f->fmt, f, 1, 0);
}

void			pf_put_buffered(const char *str, t_pf_format *f,
	size_t size, int flush_buffer)
{
	if (str && f->dest)
		while (*str && size-- && ++f->len)
			*f->dest++ = *str++;
	else if (str && !flush_buffer)
	{
		while (f->buff_size < BUFF_SIZE && size && ++f->len)
		{
			f->buff[f->buff_size++] = *str++;
			size--;
		}
		if (f->buff_size == BUFF_SIZE)
		{
			write(f->fd, f->buff, f->buff_size);
			f->buff_size = 0;
		}
		pf_put_buffered(size ? str : NULL, f, size, flush_buffer);
	}
	else if (flush_buffer && (f->fd || f->dest))
	{
		f->fd ? write(f->fd, f->buff, f->buff_size) : (*f->dest = '\0');
		f->buff_size = 0;
	}
}

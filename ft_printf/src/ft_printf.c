/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 18:45:24 by bnesoi            #+#    #+#             */
/*   Updated: 2019/07/28 18:46:42 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		internal_printf(t_pf_format *f)
{
	while (f->fmt && *f->fmt)
	{
		if (*f->fmt == '%')
		{
			f->fmt++;
			if (!*f->fmt)
				break ;
			pf_put_format(f);
			if (!*f->fmt)
				break ;
		}
		else
			pf_put_buffered(f->fmt, f, 1, 0);
		f->fmt++;
	}
	pf_put_buffered(NULL, f, 0, 1);
	return (f->len);
}

int				ft_printf(const char *format, ...)
{
	t_pf_format	f;
	int			result;

	pf_bzero(&f, sizeof(f));
	va_start(f.va_args, format);
	f.fd = 1;
	f.fmt = (char *)format;
	result = internal_printf(&f);
	va_end(f.va_args);
	return (result);
}

int				ft_fprintf(int fd, const char *format, ...)
{
	t_pf_format	f;
	int			result;

	pf_bzero(&f, sizeof(f));
	va_start(f.va_args, format);
	f.fd = fd;
	f.fmt = (char *)format;
	result = internal_printf(&f);
	va_end(f.va_args);
	return (result);
}

int				ft_sprintf(char *dest, const char *format, ...)
{
	t_pf_format	f;
	int			result;

	pf_bzero(&f, sizeof(f));
	va_start(f.va_args, format);
	f.dest = dest;
	f.fmt = (char *)format;
	result = internal_printf(&f);
	va_end(f.va_args);
	return (result);
}

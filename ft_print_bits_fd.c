/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bits_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:08:29 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:08:47 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_bits_fd(size_t size, void *ptr, int fd)
{
	unsigned int	n;
	unsigned char	*p;

	while (size--)
	{
		n = 128;
		p = (unsigned char *)ptr;
		while (n)
		{
			ft_putchar_fd((n & p[size]) ? '1' : '0', fd);
			n = n >> 1u;
		}
	}
}

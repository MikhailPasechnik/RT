/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:08:51 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:09:19 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	unsigned int	wc;

	wc = c;
	if (wc < 0x80)
		write(fd, &wc, 1);
	else if (wc < 0x800)
		write(fd, &wc, 2);
	else if (wc < 0x10000)
		write(fd, &wc, 3);
	else
		write(fd, &wc, 4);
}

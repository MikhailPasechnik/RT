/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:09:46 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 10:43:47 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb >= 10 || nb <= -10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd((nb > 0 ? (nb % 10) : -(nb % 10)) + '0', fd);
	}
	else
	{
		if (nb < 0)
			ft_putchar_fd('-', fd);
		ft_putchar_fd((nb > 0 ? (nb % 10) : -(nb % 10)) + '0', fd);
	}
}

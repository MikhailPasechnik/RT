/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 13:09:38 by bnesoi            #+#    #+#             */
/*   Updated: 2019/07/14 16:38:40 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		key_hook(int k, t_mlx *win)
{
	return (1);
}

int		mouse_press(int button, int x, int y, t_mlx *win)
{
	return (1);
}

int		mouse_release(int button, int x, int y, t_mlx *win)
{
	return (1);
}

int		mouse_move(int x, int y, t_mlx *win)
{
	return (1);
}

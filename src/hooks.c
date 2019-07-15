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

int		key_press(int k, t_mlx *win)
{
	printf("key_press: %d\n", k);
	k == KEY_ESC ? finish(win) : 0;
	return (1);
}

int		mouse_press(int button, int x, int y, t_mlx *win)
{
	printf("mouse_press: %d\n", button);
	return (1);
}

int		mouse_release(int button, int x, int y, t_mlx *win)
{
	printf("mouse_release: %d\n", button);
	return (1);
}

int		mouse_move(int x, int y, t_mlx *win)
{
	printf("mouse_move: %d %d\n", x, y);
	return (1);
}

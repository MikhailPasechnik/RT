/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2019/06/21 12:52:38 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    init_mlx(t_mlx *mlx)
{
    mlx->mlx_ptr = mlx_init();
    mlx->size_x = WIN_X;
    mlx->size_y = WIN_Y;
    mlx->win_ptr = mlx_new_window(
            mlx->mlx_ptr, mlx->size_x, mlx->size_y, WIN_TITLE);
    mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->size_x, mlx->size_y);
    mlx->pic_ptr = (int *)mlx_get_data_addr(
            mlx->img_ptr, &mlx->bpp, &mlx->size_line, &mlx->endian);
    mlx_key_hook(mlx->win_ptr,  &key_press, mlx);
    mlx_hook(mlx->win_ptr, 17, 0, &finish, mlx);
}

void    start()
{
    t_mlx mlx;
    init_mlx(&mlx);
    mlx_loop(mlx.mlx_ptr);
}

int		main(int argc, char **argv)
{
	if (argc != 1)
	{
		ft_putstr(USG_MSG);
		return (0);
	}
    start();
	return (0);
}

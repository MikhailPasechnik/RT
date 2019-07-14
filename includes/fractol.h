/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:13:17 by bnesoi            #+#    #+#             */
/*   Updated: 2019/07/14 16:38:37 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

# include "libft.h"
# include "mlx.h"
# include "keys.h"

# define WIN_X 500
# define WIN_Y 300
# define T_INC 10
# define R_INC 5
# define USG_MSG	"./fractol"
# define WIN_TITLE	"Fractol"

typedef struct	s_color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}				t_color;
# define COLOR(r, g, b)((t_color){r, g, b})
# define PACK_COLOR(c)((((unsigned)((c.r << 8u) + c.g) << 8u) + c.b))

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void        *img_ptr;
	unsigned	size_x;
	unsigned	size_y;

	int        *pic_ptr;
	int        bpp;
	int        size_line;
	int        endian;

}				t_mlx;

int				finish(t_mlx *mlx);

/*
** Hooks
*/

int		key_press(int k, t_mlx *win);
int		mouse_press(int button, int x, int y, t_mlx *win);
int		mouse_release(int button, int x, int y, t_mlx *win);
int		mouse_move(int x, int y, t_mlx *win);
#endif

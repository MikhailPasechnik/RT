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

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <stdio.h>

# include "libft.h"
# include "keys.h"
# include "ocl.h"


# define SCREEN_WIDTH 500
# define SCREEN_HEIGHT 300
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

typedef struct	s_app
{
}				t_app;

int				finish(t_app *app);

#endif

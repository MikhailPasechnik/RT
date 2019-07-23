/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:13:17 by bnesoi            #+#    #+#             */
/*   Updated: 2019/07/14 16:38:37 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <math.h>
# include <stdio.h>

# include "libft.h"
# include "keys.h"
# include "ocl.h"
# include "math3d.h"
# include "SDL.h"


# define SCREEN_WIDTH 500
# define SCREEN_HEIGHT 300

typedef struct	s_view
{
	SDL_Window	*win;
}				t_view;


typedef struct	s_app
{
	t_ocl		ocl;

}				t_app;

#endif

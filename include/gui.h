/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2020/07/08 19:43:55 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include <GL/glew.h>
# include <SDL.h>
# include <SDL_opengl.h>

# define NK_INCLUDE_FIXED_TYPES
# define NK_INCLUDE_STANDARD_IO
# define NK_INCLUDE_STANDARD_VARARGS
# define NK_INCLUDE_DEFAULT_ALLOCATOR
# define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
# define NK_INCLUDE_FONT_BAKING
# define NK_INCLUDE_DEFAULT_FONT

# include "nuklear.h"
# include "nuklear_sdl_gl3.h"

# define GUI_MAX_VERTEX_MEMORY 512 * 1024
# define GUI_MAX_ELEMENT_MEMORY 128 * 1024
# define GUI_WIN_WIDTH 400
# define GUI_WIN_HEIGHT 800
# define CMP_CLR(r1, g1, b1, r2, g2, b2) (r1 == r2 && g1 == g2 && b1 == b2)


typedef struct	s_gui
{
	SDL_Window			*win;
	SDL_GLContext		glContext;
	struct nk_context	*ctx;
}				t_gui;

int				gui_setup(t_gui *gui);

//#include "../src/gui/gui_setup.c"

#endif //GUI_H

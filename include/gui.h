/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2020/08/05 16:42:46 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include <GL/glew.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_opengl.h>
# include "m3d.h"

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
# define GUI_WIN_WIDTH 700
# define GUI_WIN_HEIGHT 800
# define CMP_CLR(r1, g1, b1, r2, g2, b2) (r1 == r2 && g1 == g2 && b1 == b2)
# define CMP_VEC(v1, v2) (v1->x == v2->x && v1->y == v2->y && v1->z == v2->z)

typedef struct			s_gui
{
	SDL_Window			*win;
	SDL_GLContext		gl_context;
	struct nk_context	*ctx;
}						t_gui;

int						gui_setup(t_gui *gui);
int						gui_destroy(t_gui *gui);
unsigned int			gui_color_pick(t_color *clr, char *lbl,
	struct nk_context *ctx);
unsigned int			gui_gray_pick(t_real *clr, char *lbl,
	struct nk_context	*ctx);
unsigned int			gui_vec_pick(t_vec3 *vec, char *lbl,
	struct nk_context	*ctx);
unsigned int			gui_single_pick(t_real *v, char *lbl,
	struct nk_context	*ctx);

#endif

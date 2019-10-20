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
# include "libft.h"
# include "ft_printf.h"
# include "ocl.h"
# include "m3d.h"
# include "SDL.h"

# define RT_WIN_FLAGS SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
# define RT_WIN_NAME "RTv1"
# define RT_WIN_WIDTH 500
# define RT_WIN_HEIGHT 300

/*
** Rt OpenCL source setup
*/
# ifdef __APPLE__
#  define RT_CL_INCLUDE "-I res/cl"
# else
#  define RT_CL_INCLUDE "-I./res/cl"
# endif
# define RT_CL_SRC "res/ocl/k_render.cl"

typedef struct	s_renderer
{
	cl_kernel 			render_kernel;

	cl_program			program;
	cl_command_queue	queue;

	char				**src;
	size_t				src_count;

	cl_mem				out_mem;
	int					out_w;
	int					out_h;

	int					width;
	int					height;
}				t_renderer;

typedef struct	s_app
{
	SDL_Window			*win;
	int					width;
	int					height;
	int 				quit;

	SDL_Rect			rect;

	t_renderer			ren;
	t_ocl				ocl;
}				t_app;

/*
** App functions
*/
int				app_start(t_app *app, char **argv, int argc);
void			app_finish(t_app *app);
void			on_app_event(t_app *app, SDL_Event *event);

/*
** Event functions
*/
void			on_mouse_move(SDL_MouseMotionEvent *event, t_app *app, int *changed);
void			on_window_size_change(SDL_WindowEvent *event, t_app *app, int *changed);
void			on_mouse_wheel(SDL_MouseWheelEvent *event, t_app *app, int *changed);
void			on_key_press(SDL_KeyboardEvent *event, t_app *app, int *changed);

/*
** Render functions
*/
int				new_renderer(t_renderer *ren, t_ocl *ocl, char *src, char *options);
void			delete_renderer(t_renderer *ren);
int				render(t_renderer *ren, t_ocl *ocl, cl_int *result, SDL_Rect *rect);

/*
** Utils functions
*/
size_t			rt_tab_len(char **tab);
void			*rt_tab_free(char **tab);
void			*rt_set_rect(SDL_Rect *rect, int x, int y, int w, int h);
#endif

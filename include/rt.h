/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:13:17 by bnesoi            #+#    #+#             */
/*   Updated: 2020/03/01 20:39:33 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <math.h>
# include "../libft/libft.h"
# include "ft_printf.h"
# include "ocl.h"
# include "m3d.h"
//# include "SDL.h"
# include "obj.h"

# define RT_WIN_FLAGS SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
# define RT_WIN_NAME "RTv1"
# define RT_WIN_WIDTH 500
# define RT_WIN_HEIGHT 300
#include <windows.h>
/*
** Rt OpenCL source setup
*/
# ifdef __APPLE__
#  define RT_CL_INCLUDE "-I res/ocl -I include"
# else
#  define RT_CL_INCLUDE "-I./res/ocl -I./include"
# endif
# define RT_CL_SRC "res/ocl/k_render.cl res/ocl/mat44.cl res/ocl/trace.cl res/ocl/utils.cl res/ocl/k_select.cl"
# define RT_K_RENDER "k_render"
# define RT_K_SELECT "k_select"
# define RT_K_OPTIONS_ARG 0
# define RT_K_CAMERA_ARG 1
# define RT_K_SCENE_ARG 2
# define RT_K_LIGHTS_ARG 3
# define RT_K_OUTPUT_ARG 4

/*
 * Rectangle
 * 		orig: rectangle start position
 * 		size: is width and height
 *
 * 	Can be used to specify kernel work area
 *   clEnqueueNDRangeKernel(q, k, 2, &r.orig, &r.size, NULL, 0, NULL, NULL);
*/
typedef struct	s_urect
{
	size_t orig[2];
	size_t size[2];
}				t_urect;

typedef struct			s_renderer
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
}						t_renderer;

//typedef struct			s_app
//{
//	SDL_Window			*win;
//	int					width;
//	int					height;
//	int 				quit;
//
//	SDL_Rect			rect;
//
//	t_renderer			ren;
//	t_ocl				ocl;
//
//	t_cam				cam;
//	t_obj				*obj;
//	t_light				*light; //
//
//	int					obj_sum; // objects of scene
//	int					light_sum; // lights of scene
//
//	int					obj_count;
//	int					light_count;
//
//	int					lines; // lines of buf
//	char				**scene; // scene for parser
//}						t_app;

/*
** App functions
*/
//int				app_start(t_app *app, char **argv, int argc);
//void			app_finish(t_app *app);
//void			on_app_event(t_app *app, SDL_Event *event);

/*
** Event functions
*/
//void			on_mouse_move(SDL_MouseMotionEvent *event, t_app *app, int *changed);
//void			on_window_size_change(SDL_WindowEvent *event, t_app *app, int *changed);
//void			on_mouse_wheel(SDL_MouseWheelEvent *event, t_app *app, int *changed);
//void			on_key_press(SDL_KeyboardEvent *event, t_app *app, int *changed);

/*
** Render functions
*/
int				new_renderer(t_renderer *ren, t_ocl *ocl, char *src, char *options);
void			delete_renderer(t_renderer *ren);
int				render(t_renderer *ren, t_ocl *ocl, cl_int *result, int *rect);

/*
** Utils functions
*/
size_t			rt_tab_len(char **tab);
void			*rt_tab_free(char **tab);
void			*rt_set_rect(int *rect, int x, int y, int w, int h);

/*
** Kate functions
*/
//int				kill(char *message);
//void			parser(t_app *app, char *scene);
//char			**read_scene(int fd, int *lines);
//void			check_obj(t_app *app);
//void			app_init(t_app *app);
//void			parser_cam(t_cam *cam, char **scn);
//void			parser_light(char **scn, t_app *app, int n);
//void			parser_obj(char **scn, t_app *app, int n);
//t_light			*add_ll(t_app *app, t_light *ll);
//t_obj			*add_ol(t_app *app, t_obj *ol);
//t_vec			array_attack(char *s);
//t_color			array_color(char *s);
//t_color			col_init(int r, int g, int b);
//t_vec			vec_init(double x, double y, double z);
//void			ignore_str(char **ptr);
//int				ptr_atoi(char **str);

#endif

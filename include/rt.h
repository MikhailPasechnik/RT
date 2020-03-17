/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:13:17 by bnesoi            #+#    #+#             */
/*   Updated: 2020/03/17 13:15:09 by bmahi            ###   ########.fr       */
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
# include "obj.h"
# include "file_io.h"

# define RT_WIN_FLAGS SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
# define RT_WIN_NAME "RTv1"
# define RT_WIN_WIDTH 1000
# define RT_WIN_HEIGHT 1000
# define RT_BUF_EXTRA 50

/*
** Rt OpenCL source setup
*/
# ifdef __APPLE__
#  define RT_CL_INCLUDE "-I res/ocl -I include"
# else
#  define RT_CL_INCLUDE "-I./res/ocl -I./include"
# endif

# define RT_CL_SRC1 "res/ocl/k_render.cl res/ocl/mat44.cl"
# define RT_CL_SRC RT_CL_SRC1" res/ocl/trace.cl res/ocl/utils.cl res/ocl/ray.cl"
# define RT_K_RENDER "k_render"
# define RT_K_OPTIONS_ARG 0
# define RT_K_CAMERA_ARG 1
# define RT_K_OBJ_ARG 2
# define RT_K_LIGHTS_ARG 3
# define RT_K_COLOR_ARG 4
# define RT_K_INDEX_ARG 5
# define RT_K_NORMA_ARG 6
# define RT_K_DEPTH_ARG 7

typedef t_list	t_obj_list;
typedef t_list	t_light_list;

typedef struct			s_phelp
{
	char				str[NAME_MAX];
	int					len;
	void				*p;
	void				(*f)(char *, void *);
}						t_phelp;

typedef struct			s_urect
{
	size_t				orig[2];
	size_t				size[2];
}						t_urect;

typedef struct			s_buffer
{
	cl_mem				device;
	void				*host;
	int					valid;
	size_t				size;
}						t_buffer;

typedef struct			s_tx_buffer
{
	cl_mem				device;
	SDL_Texture			*host;
	int					valid;
	size_t				width;
	size_t				height;
}						t_tx_buffer;

typedef struct			s_renderer
{
	cl_kernel			render_kernel;

	cl_program			program;
	cl_command_queue	queue;

	char				**src;
	size_t				src_count;

	t_buffer			obj_buf;
	t_buffer			light_buf;
	t_tx_buffer			color_buf;
	t_buffer			index_buf;
	t_tx_buffer			depth_buf;
	t_tx_buffer			normal_buf;

	t_uint				width;
	t_uint				height;
}						t_renderer;

typedef struct			s_app
{
	SDL_Window			*win;
	SDL_Renderer		*renderer;
	int					quit;

	t_renderer			ren;
	t_ocl				ocl;
	int					render_buffer;

	t_options			op;

	t_cam				cam;
	t_obj_list			*obj_list;
	t_light_list		*light_list;

	int					op_changed;
	int					cm_changed;

	int					lines;
	char				**scene;
}						t_app;

/*
** App functions
*/
int						app_start(t_app *app, char **argv, int argc);
void					app_finish(t_app *app);
int						app_error(const char *msg, int returns);
int						app_update_buffers(t_app *app);
void					on_app_event(t_app *app, SDL_Event *event);

/*
** GPU and CPU buffer management functions
*/
/*
** Transfer scene objects linked lists to CPU|GPU buffer
*/
t_buffer				create_buffer(cl_context ctx, size_t size,
	unsigned int flags);
int						push_buffer(cl_command_queue queue,
	t_buffer *buffer, size_t size, size_t offset);
int						pull_buffer(cl_command_queue queue,
	t_buffer *buffer, size_t size, size_t offset);
int						free_buffer(t_buffer *buffer);
t_tx_buffer				create_tx_buffer(t_app *app, size_t width,
	size_t height, unsigned int flags);
int						push_tx_buffer(cl_command_queue queue,
	t_tx_buffer *buffer, size_t offset);
int						pull_tx_buffer(cl_command_queue queue,
	t_tx_buffer *buffer, size_t offset);
int						free_tx_buffer(t_tx_buffer *buffer);
int						transfer_objects(t_app *app);
int						transfer_light(t_app *app);
/*
** Partial buffer update
*/
int						update_light(t_app *app, int index, t_light *light);
int						update_object(t_app *app, int index, t_obj *obj);

/*
**  Kernel arguments update
*/
int						update_camera(cl_kernel kernel, t_cam *cam,
	int arg_num);
int						update_options(cl_kernel kernel,
	t_options *options, int arg_num);

/*
** Event functions
*/
void					on_mouse_move(SDL_MouseMotionEvent *event,
	t_app *app, int *changed);
void					on_window_size_change(SDL_WindowEvent *event,
	t_app *app, int *changed);
void					on_mouse_wheel(SDL_MouseWheelEvent *event,
	t_app *app, int *changed);
void					on_key_press(SDL_KeyboardEvent *event,
	t_app *app, int *changed);

/*
** Render functions
*/
int						new_renderer(t_renderer *ren, t_ocl *ocl,
		char *src, char *options);
void					delete_renderer(t_renderer *ren);
int						render(t_renderer *ren, t_ocl *ocl);

/*
** Utils functions
*/
size_t					rt_tab_len(char **tab);
void					*rt_tab_free(char **tab);
void					*rt_set_rect(SDL_Rect *rect, int x, int y, int w,
	int h);
t_color					get_surface_pixel(SDL_Surface *surface, size_t x,
	size_t y);
int						screen_shot(t_app *app);

/*
** Kate functions
*/
int						kill(char *message);
void					parser(t_app *app, char *scene);
char					**read_scene(int fd, int *lines);
void					parser_cam(t_cam *cam, char **scn);
void					parser_light(char **scn, t_app *app, int n);
void					parser_obj(char **scn, t_app *app, int n);
void					check_obj(t_app *app);
void					check_light(t_app *app);
t_vec3					array_attack(char *s);
t_color					array_color(char *s);
t_real					ptr_atoi(char **str);
int						ptr_atoi_int(char **str, int fraction);
void					ignore_str(char **ptr);
int						is_valid_obj_name(t_obj *ol, char *str);
int						is_valid_light_name(char *str);
int						key_type(char *s);
void					parse_real(char *str, void *vp);
void					parse_vec3(char *str, void *vp);
void					parse_color(char *str, void *vp);
void					parse_id(char *str, void *vp);

/*
** Navigation functions
*/
void					nav_move_camera(t_cam *cam, t_vec3 *by);
void					nav_rotate_camera(t_cam *cam, t_vec3 *rot,
	t_vec3 *around);

#endif

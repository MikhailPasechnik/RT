/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:13:17 by bnesoi            #+#    #+#             */
/*   Updated: 2020/08/10 16:14:24 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <math.h>
# include <time.h>
# include "libft.h"
# include "ft_printf.h"
# include "ocl.h"
# include "m3d.h"
# include <SDL2/SDL.h>
# include "obj.h"
# include "file_io.h"

# define RT_WIN_FLAGS SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
# define RT_WIN_NAME "RT"
# define RT_WIN_WIDTH 800
# define RT_WIN_HEIGHT 800
# define RT_BUF_EXTRA 0
# define RT_CLICK_THRESHOLD 100

/*
** Rt OpenCL source setup
*/
# ifdef __APPLE__
#  define RT_CL_INCLUDE "-I resources/ocl -I include"
# else
#  define RT_CL_INCLUDE "-I./resources/ocl -I./include"
# endif

# define RT_CL_SRC3 " resources/ocl/k_render.cl resources/ocl/k_postprocess.cl"
# define RT_CL_SRC2 RT_CL_SRC3" resources/ocl/mat44.cl"
# define RT_CL_SRC1 RT_CL_SRC2" resources/ocl/color.cl resources/ocl/ray.cl"
# define RT_CL_SRC RT_CL_SRC1" resources/ocl/trace.cl resources/ocl/utils.cl"
# define RT_K_RENDER "k_render"
# define RT_K_OPTIONS_ARG 0
# define RT_K_CAMERA_ARG 1
# define RT_K_OBJ_ARG 2
# define RT_K_LIGHTS_ARG 3
# define RT_K_COLOR_ARG 4
# define RT_K_INDEX_ARG 5
# define RT_K_NORMA_ARG 6
# define RT_K_DEPTH_ARG 7
# define RT_K_TEX_ARG 8
# define RT_K_TEX_I_ARG 9
# define RT_P_OBJ_FILED_NUM 12

typedef t_list	t_obj_list;
typedef t_list	t_light_list;

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
	cl_kernel			pproc_kernel;

	cl_program			program;
	cl_command_queue	queue;

	char				**src;
	size_t				src_count;

	t_buffer			obj_buf;
	t_buffer			light_buf;
	t_tx_buffer			color_buf;
	t_tx_buffer			color_buf2;
	t_buffer			index_buf;
	t_buffer			depth_buf;
	t_buffer			normal_buf;
	t_buffer			texture_buf;
	t_buffer			texture_info_buf;

	t_uint				width;
	t_uint				height;
	int					pproc_enabled;
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
	t_list				*tx_list;
	t_list				*tx_info_list;
	t_list				*tx_src_list;

	int					op_changed;
	int					cm_changed;

	int					lines;
	char				**scene;
	unsigned			parse_error;

	Uint32				ts_mouse_down;

	t_int				selection;
}						t_app;

typedef struct			s_phelp
{
	char				str[NAME_MAX];
	int					len;
	void				*p;
	void				(*f)(char *, void *, t_app *);
	t_app				*app;
}						t_phelp;

/*
** App functions
*/
int						app_start(t_app *app, char **argv, int argc);
void					app_finish(t_app *app);
int						app_error(const char *msg, int returns);
int						app_update_buffers(t_app *app);
int						app_render(t_app *app);
void					on_app_event(t_app *app, SDL_Event *event);
void					init_options(t_options *op);

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
int						transfer_textures(t_app *app);
int						transfer_texture_info(t_app *app);
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
void					on_mouse_click(SDL_MouseButtonEvent *event,
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
void					file_name(char name[150]);
int						screen_shot(t_app *app);
size_t					list_size(t_list *lst);

/*
** Parser functions
*/
int						kill(char *message);
void					parser(t_app *app, char *scene);
char					**read_scene(int fd, int *lines);
int						parser_cam(t_cam *cam, char **scn, t_app *app);
void					parser_light(char **scn, t_app *app, int n);
void					parser_obj(char **scn, t_app *app, int n);
void					check_obj(t_app *app);
void					check_light(t_app *app);
t_vec3					array_attack(char *s);
t_color					array_color(char *s);
t_real					ptr_atoi(char **str);
int						ptr_atoi_int(char **str, int fraction);
void					ignore_str(char **ptr, int c);
int						is_valid_obj_name(t_obj *ol, char *str);
int						is_valid_light_name(char *str);
int						key_type(char *s);
void					parse_real(char *str, void *vp, t_app *app);
void					parse_vec3(char *str, void *vp, t_app *app);
void					parse_color(char *str, void *vp, t_app *app);
void					parse_id(char *str, void *vp, t_app *app);
void					parse_texture(char *str, void *id, t_app *app);
void					app_delete_linked_lists(t_app *app);
/*
** Print RT scene functions
*/
int						save_scene(t_app *app);
void					printing_light(int fd, t_app *app);
void					printing_obj(int fd, t_app *app);
void					print_parametrs(int fd, t_obj *obj);
void					print_tx(int fd, t_app *app, t_obj	*obj);
/*
** Navigation functions
*/
void					nav_move_camera(t_cam *cam, t_vec3 *by);
void					nav_rotate_camera(t_cam *cam, t_vec3 *rot,
	t_vec3 *around);

#endif

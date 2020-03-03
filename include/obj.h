/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 15:34:22 by bmahi             #+#    #+#             */
/*   Updated: 2020/03/01 20:38:58 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

#include "../include/m3d.h"
# include "../include/rt.h"

# define ID_SPH	1
# define ID_PLN	2
# define ID_CYL 3
# define ID_CON	4

# define NLL 0.000001
# define COLOR(r, g, b) ((t_color){r, g, b})

typedef struct			s_color
{
	cl_uchar			r;
	cl_uchar			g;
	cl_uchar			b;
}						t_color; // cl_int - ? 

typedef struct			s_cam
{
	t_vec3				pos;
	t_vec3				dir;
	t_vec3				rot;
}						t_cam;

typedef struct			s_obj
{
	t_vec3				pos;
	t_vec3				rot;
	t_color				color;
	cl_double			r;
	cl_int				name;
	cl_double			specul;
	cl_double			reflect;
	struct s_obj		*next;
}						t_obj;

typedef	struct			s_light
{
	t_vec3				pos;
	double				inten;
	t_color				color;
//	t_vec				vec_p;
//	t_vec				vec_n;
//	cl_double			new_inten;
	struct s_light		*next;	
}						t_light;

typedef struct			s_cl
{
	cl_context			context;
	cl_command_queue	queue;
	cl_platform_id		*plat_id;
	cl_device_id		*dev_id;
	cl_uint				num_plat;
	cl_uint				num_dev;
	cl_kernel			kernel;
	cl_program			prog;
	cl_mem				obj_mem;
	cl_mem				light_mem;
	cl_mem				img;
	cl_mem				d_mem;
	cl_mem				i_mem;
	t_obj				*cl_obj;
	t_light				*cl_light;
	int					*data;
	int 				o_count;
	int 				l_count;
}						t_cl;

#endif
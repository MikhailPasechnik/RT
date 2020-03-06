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
# define ID_CUB	5
# define IS_SPH(o) ((o)->id == (ID_SPH))
# define IS_PLN(o) ((o)->id == (ID_PLN))
# define IS_CYL(o) ((o)->id == (ID_CYL))
# define IS_CON(o) ((o)->id == (ID_CON))
# define IS_CUB(o) ((o)->id == (ID_CUB))

# define NLL 0.000001
# define COLOR(r, g, b) ((t_color){r, g, b})

/*
**
**
** Recommend declaring your structure from the widest types first
** down to the narrowest types.
** First, this avoids wasted unused spaces due to alignment.
** Second, this often avoids any headaches
** with different alignments on different devices.
*/


typedef struct			s_color
{
	cl_uchar			r;
	cl_uchar			g;
	cl_uchar			b;
}						t_color;

typedef struct			s_cam
{
	t_vec3				pos;
	t_vec3				dir;
	t_vec3				rot;
}						t_cam;

typedef struct 			s_mat
{
	t_vec3				diffuse;
	cl_double			specular;
}						t_mat;

typedef struct			s_obj
{
	t_mat				mat;
	t_vec3				pos;
	t_vec3				rot;

	t_real				radius;
	t_real				height;
	cl_int				id;
}						t_obj;

typedef	struct			s_light
{
	t_vec3				pos;
	t_vec3				dir;
	t_color				color;
}						t_light;

typedef t_list t_obj_list;
typedef t_list t_light_list;

#endif
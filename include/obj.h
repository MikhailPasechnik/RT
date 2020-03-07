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

# ifndef OBJ_H
# define OBJ_H

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

typedef cl_double       t_real;
typedef cl_double16     t_mat4;
typedef cl_double3      t_vec3;
typedef cl_int          t_int;
typedef cl_uint         t_uint;

/*
** OpenCL compatible structs
**
** Recommend declaring your structure from the widest types first
** down to the narrowest types.
** First, this avoids wasted unused spaces due to alignment.
** Second, this often avoids any headaches
** with different alignments on different devices.
*/

typedef struct          s_options
{
    t_real              fov;
    t_uint              width;
    t_uint              height;
    t_uint              scene_size;
    t_uint              lights_size;
    t_uint              cameras_size;
}                       t_options;

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
	t_int				id;
	t_int				symbol;
}						t_obj;

typedef	struct			s_light
{
	t_vec3				pos;
	t_vec3				dir;
    t_vec3				diffuse;
}						t_light;

typedef	struct	s_ray {
    t_vec3	orig;
    t_vec3	dir;
    t_real	t;
}				t_ray;

typedef struct	s_hit_cpu {
    t_vec3	pos;
    t_vec3	norm;
    t_uint  obj_index;
}				t_hit_cpu;

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 15:34:22 by bmahi             #+#    #+#             */
/*   Updated: 2020/03/17 13:15:14 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

/*
** Check that we are compiling on device and define types without "cl_" prefix.
** Else define types with "cl_" prefix.
*/
# ifdef __APPLE__
#  include <OpenCL/opencl.h>

typedef cl_float		t_real;
typedef cl_float16		t_mat4;
typedef cl_float3		t_vec3;
typedef cl_int			t_int;
typedef cl_uint			t_uint;
typedef cl_float3		t_color;
# endif

# define ID_SPH	1
# define ID_PLN	2
# define ID_CYL 3
# define ID_CON	4
# define ID_CUB	5
# define ID_DIRECT 1
# define ID_POINT 2
# define ID_AMB 3
# define T_SPH "sphere"
# define T_PLN "plane"
# define T_CYL "cylinder"
# define T_CON "cone"
# define T_CUB "cube"
# define T_LIGHT "light"
# define T_CAM "camera"
# define IS_SPH(o) ((o)->id == (ID_SPH))
# define IS_PLN(o) ((o)->id == (ID_PLN))
# define IS_CYL(o) ((o)->id == (ID_CYL))
# define IS_CON(o) ((o)->id == (ID_CON))
# define IS_CUB(o) ((o)->id == (ID_CUB))

/*
** OpenCL compatible structs
**
** Recommend declaring your structure from the widest types first
** down to the narrowest types.
** First, this avoids wasted unused spaces due to alignment.
** Second, this often avoids any headaches
** with different alignments on different devices.
*/

typedef struct			s_options
{
	t_vec3				background_color;
	t_real				reflection_depth;
	t_uint				width;
	t_uint				height;
	t_uint				obj_count;
	t_uint				light_count;
}						t_options;

typedef struct			s_cam
{
	t_mat4				mtx;
	t_real				fov;
}						t_cam;

typedef struct			s_mat
{
	t_color				diffuse;
	t_real				specular;
	t_real				refraction;
	t_real				ior;
	t_real				fresnel;
	t_real				reflection;
}						t_mat;

typedef struct			s_obj
{
	t_mat				mat;
	t_vec3				pos;
	t_vec3				rot;
	t_real				radius;
	t_real				height;
	t_real				infinite;
	t_int				id;
}						t_obj;

typedef struct			s_light
{
	t_vec3				pos;
	t_vec3				rot;
	t_color				color;
	t_real				intensity;
	t_int				id;
}						t_light;

typedef struct			s_ray
{
	t_vec3				o;
	t_vec3				d;
	t_real				t;
}						t_ray;

typedef struct			s_hit_cpu
{
	t_vec3				pos;
	t_vec3				norm;
	t_uint				obj_index;
}						t_hit_cpu;

#endif

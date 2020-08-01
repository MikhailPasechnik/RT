/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 15:34:22 by bmahi             #+#    #+#             */
/*   Updated: 2020/08/01 22:04:00 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

/*
** Check that we are compiling on device and define types without "cl_" prefix.
** Else define types with "cl_" prefix.
*/
# ifdef HOST_DEVICE
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/opencl.h>
# endif
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
# define ID_PAR	6
# define ID_PCL	7
# define ID_ELL	8
# define ID_HCL	9
# define ID_HTS	10
# define ID_HPR	11
# define ID_DIRECT 1
# define ID_POINT 2
# define ID_AMB 3
# define T_SPH "sphere"
# define T_PLN "plane"
# define T_CYL "cylinder"
# define T_CON "cone"
# define T_CUB "cube"
# define T_PAR "paraboloid"
# define T_PCL "parabolic cylinder"
# define T_ELL "ellipse"
# define T_HCL "hyperbolic cylinder"
# define T_HTS "hyperboloid with two sheets"
# define T_HPR "hyperbolic paraboloid"
# define T_LIGHT "light"
# define T_CAM "camera"
# define IS_SPH(o) ((o)->id == (ID_SPH))
# define IS_PLN(o) ((o)->id == (ID_PLN))
# define IS_CYL(o) ((o)->id == (ID_CYL))
# define IS_CON(o) ((o)->id == (ID_CON))
# define IS_CUB(o) ((o)->id == (ID_CUB))
# define IS_PAR(o) ((o)->id == (ID_PAR))
# define IS_PCL(o) ((o)->id == (ID_PCL))
# define IS_ELL(o) ((o)->id == (ID_ELL))
# define IS_HCL(o) ((o)->id == (ID_HCL))
# define IS_HTS(o) ((o)->id == (ID_HTS))
# define IS_HPR(o) ((o)->id == (ID_HPR))

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
	t_uint				trace_changed;
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
	t_color				emittance;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 01:52:14 by bmahi             #+#    #+#             */
/*   Updated: 2020/03/17 02:28:14 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M3D_H
# define M3D_H

# include "libft.h"
# include <math.h>
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/opencl.h>
# endif
# define EPSILON 0.000001
# define R_ABS fabs
# define R_ROUND round
# define R_SQRT sqrt
# ifndef M_PI
#  define M_PI 3.14159265
# endif
# define TO_RAD(a)((a / 2)*(M_PI / 180.0))

typedef cl_float	t_real;
typedef cl_float16	t_mat4;
typedef cl_float3	t_vec3;
typedef cl_int		t_int;
typedef cl_uint		t_uint;
typedef cl_float3	t_color;
# define VEC(x, y, z)((t_vec3){{x, y, z}})
# define COLOR(r, g, b, a) ((t_color){{r, g, b}})

/*
** Helper to access cl_double16 by row and column on pointer var
*/

# define M44(m, r, c)(m->s[r * 4 + c])

/*
** Helper to access cl_double16 by row and column on static var
*/

# define M44S(m, r, c)(m.s[r * 4 + c])

/*
** Matrix3 ops
*/
t_mat4				*m4_mul(t_mat4 *a, t_mat4 *b, t_mat4 *out);
t_vec3				*m4_v3_mul(t_mat4 *a, t_vec3 *b, t_vec3 *out);
t_mat4				*m4_identity(t_mat4 *m);
int					m4_is_identity(t_mat4 *m);
t_mat4				*m4_copy(t_mat4 *m, t_mat4 *out);
void				m4_translate(t_mat4 *m, t_vec3 *t);
void				m4_rotate(t_mat4 *m, t_vec3 *r);
void				m4_set_rotation(t_mat4 *m, t_vec3 *r);
void				m4_scale(t_mat4 *m, t_vec3 *s);
void				m4_set_translate(t_mat4 *m, t_vec3 *t);
t_vec3				*m4_extract_translation(t_mat4 *m, t_vec3 *out);
t_vec3				*m4_extract_scale(t_mat4 *m, t_vec3 *out);
t_mat4				*m4_extract_rotation(t_mat4 *m, t_mat4 *out);
void				m4_rotate_relative(t_mat4 *m, t_mat4 *p, t_vec3 *rot);
t_mat4				look_at(t_vec3 from, t_vec3 to);

/*
** TODO: Determinant and Inverse
**		implement this?
**		https://www.sanfoundry.com/c-program-find-inverse-matrix/
*/
t_real				m4_det(t_mat4 *m);
t_mat4				*m4_inv(t_mat4 *m, t_mat4 *out);

/*
** Vec3 ops
*/
t_real				v3_mag(t_vec3 *v);
t_vec3				*v3_add(t_vec3 *a, t_vec3 *b, t_vec3 *out);
t_vec3				*v3_sub(t_vec3 *a, t_vec3 *b, t_vec3 *out);
t_real				v3_dot(t_vec3 *a, t_vec3 *b);
t_vec3				*v3_cross(t_vec3 *a, t_vec3 *b, t_vec3 *out);
t_vec3				*v3_norm(t_vec3 *v, t_vec3 *out);
t_vec3				*v3_mull_s(t_vec3 *v, t_real s, t_vec3 *out);
t_vec3				*v3_copy(t_vec3 *v, t_vec3 *out);

#endif

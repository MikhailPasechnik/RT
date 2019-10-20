/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssheba <ssheba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:27:06 by bnesoi            #+#    #+#             */
/*   Updated: 2019/07/14 12:34:07 by ssheba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M3D_H
# define M3D_H

# include "libft.h"
# include <math.h>

# define EPSILON 0.000001
# define R_ABS fabs
# define R_ROUND round
# define TO_RAD(a)((a)*(M_PI / 180.0))

typedef double	t_m3d_real;
typedef struct	s_m3d_mat4
{
	t_m3d_real	r[4][4];
}				t_mat4;
typedef struct	s_m3d_vec3
{
	t_m3d_real	x;
	t_m3d_real	y;
	t_m3d_real	z;
}				t_m3d_vec3;
# define VEC(x, y, z)((t_vec3){x, y, z})

/*
** Matrix3 ops
*/
t_mat4			*m3d_m4_mul(t_mat4 *a, t_mat4 *b, t_mat4 *out);
t_m3d_vec3		*m3d_m4_v3_mul(t_mat4 *a, t_m3d_vec3 *b, t_m3d_vec3 *out);
t_mat4			*m3d_m4_identity(t_mat4 *m);
int				m3d_m4_is_identity(t_mat4 *m);
t_mat4			*m3d_m4_copy(t_mat4 *m, t_mat4 *out);
void			m3d_m4_translate(t_mat4 *m, t_m3d_vec3 *t);
void			m3d_m4_rotate(t_mat4 *m, t_m3d_vec3 *r);
void			m3d_m4_set_rotation(t_mat4 *m, t_m3d_vec3 *r);
void			m3d_m4_scale(t_mat4 *m, t_m3d_vec3 *s);
void			m3d_m4_set_translate(t_mat4 *m, t_m3d_vec3 *t);
t_m3d_vec3		*m3d_m4_extract_translation(t_mat4 *m, t_m3d_vec3 *out);
t_m3d_vec3		*m3d_m4_extract_scale(t_mat4 *m, t_m3d_vec3 *out);
t_mat4			*m3d_m4_extract_rotation(t_mat4 *m, t_mat4 *out);
void			m3d_m4_rotate_relative(t_mat4 *m, t_m3d_vec3 *p, t_m3d_vec3 *rot);

/*
** TODO: Determinant and Inverse
**		implement this?
**		https://www.sanfoundry.com/c-program-find-inverse-matrix/
*/
t_m3d_real		m3d_m4_det(t_mat4 *m);
t_mat4			*m3d_m4_inv(t_mat4 *m, t_mat4 *out);

/*
** Vec3 ops
*/
t_m3d_real		m3d_v3_mag(t_m3d_vec3 *v);
t_m3d_vec3		*m3d_v3_add(t_m3d_vec3 *a, t_m3d_vec3 *b, t_m3d_vec3 *out);
t_m3d_vec3		*m3d_v3_sub(t_m3d_vec3 *a, t_m3d_vec3 *b, t_m3d_vec3 *out);
t_m3d_vec3		*m3d_v3_cross(t_m3d_vec3 *a, t_m3d_vec3 *b, t_m3d_vec3 *out);
t_m3d_vec3		*m3d_v3_norm(t_m3d_vec3 *v, t_m3d_vec3 *out);
t_m3d_vec3		*m3d_v3_mull_s(t_m3d_vec3 *v, t_m3d_real s, t_m3d_vec3 *out);
t_m3d_vec3		*m3d_v3_copy(t_m3d_vec3 *v, t_m3d_vec3 *out);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_rts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssheba <ssheba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:33:58 by bnesoi            #+#    #+#             */
/*   Updated: 2019/07/14 12:29:37 by ssheba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m3d.h"

t_mat4			*m4_extract_rotation(t_mat4 *m, t_mat4 *out)
{
	t_vec3 s;

	if (!m || !out)
		return (NULL);
	m4_extract_scale(m, &s);
	m4_identity(out);
	M44(out, 0, 0) = M44(m, 0, 0) / s.x;
	M44(out, 0, 1) = M44(m, 0, 1) / s.y;
	M44(out, 0, 2) = M44(m, 0, 2) / s.z;
	M44(out, 1, 0) = M44(m, 1, 0) / s.x;
	M44(out, 1, 1) = M44(m, 1, 1) / s.y;
	M44(out, 1, 2) = M44(m, 1, 2) / s.z;
	M44(out, 2, 0) = M44(m, 2, 0) / s.x;
	M44(out, 2, 1) = M44(m, 2, 1) / s.y;
	M44(out, 2, 2) = M44(m, 2, 2) / s.z;
	return (out);
}

t_vec3			*m4_extract_translation(t_mat4 *m, t_vec3 *out)
{
	if (!m || !out)
		return (NULL);
	out->x = M44(m, 3, 0);
	out->y = M44(m, 3, 1);
	out->z = M44(m, 3, 2);
	return (out);
}

t_vec3			*m4_extract_scale(t_mat4 *m, t_vec3 *out)
{
	if (!m || !out)
		return (NULL);
	out->x = v3_mag(&VEC(m->s0, m->s1, m->s2));
	out->y = v3_mag(&VEC(m->s4, m->s5, m->s6));
	out->z = v3_mag(&VEC(m->s8, m->s9, m->sa));
	return (out);
}

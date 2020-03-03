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
	out->r[0][0] = m->r[0][0] / s.x;
	out->r[0][1] = m->r[0][1] / s.y;
	out->r[0][2] = m->r[0][2] / s.z;
	out->r[1][0] = m->r[1][0] / s.x;
	out->r[1][1] = m->r[1][1] / s.y;
	out->r[1][2] = m->r[1][2] / s.z;
	out->r[2][0] = m->r[2][0] / s.x;
	out->r[2][1] = m->r[2][1] / s.y;
	out->r[2][2] = m->r[2][2] / s.z;
	return (out);
}

t_vec3			*m4_extract_translation(t_mat4 *m, t_vec3 *out)
{
	if (!m || !out)
		return (NULL);
	out->x = m->r[3][0];
	out->y = m->r[3][1];
	out->z = m->r[3][2];
	return (out);
}

t_vec3			*m4_extract_scale(t_mat4 *m, t_vec3 *out)
{
	if (!m || !out)
		return (NULL);
	out->x = v3_mag((t_vec3 *) m->r[0]);
	out->y = v3_mag((t_vec3 *) m->r[1]);
	out->z = v3_mag((t_vec3 *) m->r[2]);
	return (out);
}

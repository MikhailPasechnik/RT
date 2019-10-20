/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssheba <ssheba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:33:58 by bnesoi            #+#    #+#             */
/*   Updated: 2019/07/09 15:09:06 by ssheba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m3d.h"

void	m3d_m4_rotate_relative(t_mat4 *m, t_m3d_vec3 *p, t_m3d_vec3 *rot)
{
	t_mat4	inv_rel;
	t_mat4	tmp;

	m3d_m4_set_translate(&tmp, p);
	m3d_m4_mul(m, m3d_m4_inv(&tmp, &inv_rel), m);
	m3d_m4_rotate(&tmp, rot);
	m3d_m4_mul(m, &tmp, m);
}

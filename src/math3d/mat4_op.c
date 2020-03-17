/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:33:58 by bnesoi            #+#    #+#             */
/*   Updated: 2020/03/17 02:17:53 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m3d.h"
#include <stdio.h>

/*
** M.s0, M.s1, M.s2, M.s3
** M.s4, M.s5, M.s6, M.s7
** M.s8, M.s9, M.sA, M.sB
** M.sC, M.sD, M.sE, M.sF
*/

t_mat4	look_at(t_vec3 from, t_vec3 to)
{
	t_mat4 m;
	t_vec3 forward;
	t_vec3 right;
	t_vec3 up;

	v3_norm(v3_sub(&from, &to, &forward), &forward);
	v3_cross(&VEC(0, 0, 1), &forward, &right);
	v3_cross(&forward, &right, &up);
	v3_norm(&forward, &forward);
	v3_norm(&right, &right);
	v3_norm(&up, &up);
	m4_identity(&m);
	m.s0 = right.x;
	m.s1 = right.y;
	m.s2 = right.z;
	m.s4 = up.x;
	m.s5 = up.y;
	m.s6 = up.z;
	m.s8 = forward.x;
	m.s9 = forward.y;
	m.sA = forward.z;
	m.sC = from.x;
	m.sD = from.y;
	m.sE = from.z;
	return (m);
}

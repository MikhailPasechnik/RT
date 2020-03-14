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
#include <stdio.h>
void	m4_rotate_relative(t_mat4 *m, t_mat4 *r, t_vec3 *rot)
{
	t_mat4	im;
	t_mat4	ir;

	m4_extract_rotation(m, &ir);

	m4_inv(&ir, &im);
	m4_mul(&im, r, r);
	m4_mul(r, m, m);


//	m4_mul(p, &inv_m, p);
//	m4_mul(m, p, m);
//	m4_rotate(p, rot);
//	m4_mul(m, p, m);
}

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

	printf("from=====%f %f %f=====\n", from.x, from.y, from.z );
	v3_norm(v3_sub(&from, &to, &forward), &forward);
	v3_cross(&VEC(0, 0, 1), &forward, &right);
	v3_cross(&forward, &right, &up);
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
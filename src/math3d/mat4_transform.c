/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssheba <ssheba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:33:58 by bnesoi            #+#    #+#             */
/*   Updated: 2019/07/09 15:09:06 by ssheba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m3d.h"

void	m4_translate(t_mat4 *m, t_vec3 *t)
{
	M44(m, 3, 0) +=
			t->x * M44(m, 0, 0) +
			t->y * M44(m, 1, 0) +
			t->z * M44(m, 2, 0);
	M44(m, 3, 1) +=
			t->x * M44(m, 0, 1) +
			t->y * M44(m, 1, 1) +
			t->z * M44(m, 2, 1);
	M44(m, 3, 2) +=
			t->x * M44(m, 0, 2) +
			t->y * M44(m, 1, 2) +
			t->z * M44(m, 2, 2);
	M44(m, 3, 3) +=
			t->x * M44(m, 0, 3) +
			t->y * M44(m, 1, 3) +
			t->z * M44(m, 2, 3);
}

void	m4_set_translate(t_mat4 *m, t_vec3 *t)
{
	m4_identity(m);
	M44(m, 3, 0) = t->x;
	M44(m, 3, 1) = t->y;
	M44(m, 3, 2) = t->z;
}

void	m4_set_rotation(t_mat4 *m, t_vec3 *r)
{
	t_real	cos_v[3];
	t_real	sin_v[3];

	m4_identity(m);
	cos_v[2] = cos(TO_RAD(r->z));
	cos_v[1] = cos(TO_RAD(r->y));
	cos_v[0] = cos(TO_RAD(r->x));
	sin_v[2] = sin(TO_RAD(r->z));
	sin_v[1] = sin(TO_RAD(r->y));
	sin_v[0] = sin(TO_RAD(r->x));
	M44(m, 0, 0) = cos_v[2] * cos_v[1];
	M44(m, 0, 1) = sin_v[2] * cos_v[1];
	M44(m, 0, 2) = -sin_v[1];
	M44(m, 1, 0) = -sin_v[2] * cos_v[0] + cos_v[2] * sin_v[1] * sin_v[0];
	M44(m, 1, 1) = cos_v[2] * cos_v[0] + sin_v[2] * sin_v[1] * sin_v[0];
	M44(m, 1, 2) = cos_v[1] * sin_v[0];
	M44(m, 2, 0) = -sin_v[2] * -sin_v[0] + cos_v[2] * sin_v[1] * cos_v[0];
	M44(m, 2, 1) = cos_v[2] * -sin_v[0] + sin_v[2] * sin_v[1] * cos_v[0];
	M44(m, 2, 2) = cos_v[1] * cos_v[0];
}

void	m4_rotate(t_mat4 *m, t_vec3 *r)
{
	t_mat4	mr;
	t_mat4	mc;
	int		rr;
	int		cc;
	int		k;

	mc = *m4_copy(m, &mc);
	m4_set_rotation(&mr, r);
	rr = 3;
	while (rr--)
	{
		cc = 4;
		while (cc--)
		{
			k = 3;
			M44(m, rr, cc) = 0;
			while (k--)
				if (M44S(mc, rr, k))
					M44(m, rr, cc) += M44S(mc, rr, k) * M44S(mr, k, cc);
		}
	}
}

void	m4_scale(t_mat4 *m, t_vec3 *s)
{
	int		r;
	int		c;
	t_real	*v;

	v = (t_real *)s;
	r = 3;
	while (r--)
	{
		c = 3;
		while (c--)
			M44(m, r, c) *= v[r];
	}
}

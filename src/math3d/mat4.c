/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:40:38 by bnesoi            #+#    #+#             */
/*   Updated: 2019/07/06 15:11:21 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m3d.h"

t_mat4			*m4_mul(t_mat4 *a, t_mat4 *b, t_mat4 *out)
{
	int		r;
	int		c;
	int		k;
	t_mat4	a_copy;
	t_mat4	b_copy;

	if ((!a || !b) || !out)
		return (NULL);
	a == out ? a = m4_copy(a, &a_copy) : 0;
	b == out ? b = m4_copy(b, &b_copy) : 0;
	r = 4;
	while (r--)
	{
		c = 4;
		while (c--)
		{
			k = 4;
			out->r[r][c] = 0;
			while (k--)
				if (a->r[r][k])
					out->r[r][c] += a->r[r][k] * b->r[k][c];
		}
	}
	return (out);
}

t_vec3			*m4_v3_mul(t_mat4 *a, t_vec3 *b, t_vec3 *out)
{
	t_real	w;
	t_vec3	b_copy;

	if (!a || !b || !out)
		return (NULL);
	b == out ? b = v3_copy(b, &b_copy) : 0;
	w = b->x * a->r[0][3] +
		b->y * a->r[1][3] +
		b->z * a->r[2][3] + a->r[3][3];
	out->x = (
			b->x * a->r[0][0] +
			b->y * a->r[1][0] +
			b->z * a->r[2][0] + a->r[3][0]) / w;
	out->y = (
			b->x * a->r[0][1] +
			b->y * a->r[1][1] +
			b->z * a->r[2][1] + a->r[3][1]) / w;
	out->z = (
			b->x * a->r[0][2] +
			b->y * a->r[1][2] +
			b->z * a->r[2][2] + a->r[3][2]) / w;
	return (out);
}

static void		coefficient(t_mat4 *m, t_real *out)
{
	out[0] = m->r[1][2] * m->r[2][3] - m->r[1][3] * m->r[2][2];
	out[1] = m->r[1][2] * m->r[3][3] - m->r[1][3] * m->r[3][2];
	out[3] = m->r[2][2] * m->r[3][3] - m->r[2][3] * m->r[3][2];
	out[4] = m->r[2][1] * m->r[3][3] - m->r[2][3] * m->r[3][1];
	out[5] = m->r[1][1] * m->r[3][3] - m->r[1][3] * m->r[3][1];
	out[6] = m->r[1][1] * m->r[2][3] - m->r[1][3] * m->r[2][1];
	out[7] = m->r[2][1] * m->r[3][2] - m->r[2][2] * m->r[3][1];
	out[8] = m->r[1][1] * m->r[3][2] - m->r[1][2] * m->r[3][1];
	out[9] = m->r[1][1] * m->r[2][2] - m->r[1][2] * m->r[2][1];
	out[10] = m->r[2][0] * m->r[3][3] - m->r[2][3] * m->r[3][0];
	out[11] = m->r[2][0] * m->r[3][2] - m->r[2][2] * m->r[3][0];
	out[12] = m->r[2][0] * m->r[3][1] - m->r[2][1] * m->r[3][0];
	out[13] = m->r[1][0] * m->r[3][3] - m->r[1][3] * m->r[3][0];
	out[14] = m->r[1][0] * m->r[3][2] - m->r[1][2] * m->r[3][0];
	out[15] = m->r[1][0] * m->r[2][3] - m->r[1][3] * m->r[2][0];
	out[16] = m->r[1][0] * m->r[2][2] - m->r[1][2] * m->r[2][0];
	out[17] = m->r[1][0] * m->r[3][1] - m->r[1][1] * m->r[3][0];
	out[18] = m->r[1][0] * m->r[2][1] - m->r[1][1] * m->r[2][0];
}

static void		inv_apply(const t_real m[4][4],
							 const t_real *c, t_real o[4][4], t_real d)
{
	o[0][0] = d * (m[1][1] * c[3] - m[1][2] * c[4] + m[1][3] * c[7]);
	o[0][1] = d * -(m[0][1] * c[3] - m[0][2] * c[4] + m[0][3] * c[7]);
	o[0][2] = d * (m[0][1] * c[1] - m[0][2] * c[5] + m[0][3] * c[8]);
	o[0][3] = d * -(m[0][1] * c[0] - m[0][2] * c[6] + m[0][3] * c[9]);
	o[1][0] = d * -(m[1][0] * c[3] - m[1][2] * c[10] + m[1][3] * c[11]);
	o[1][1] = d * (m[0][0] * c[3] - m[0][2] * c[10] + m[0][3] * c[11]);
	o[1][2] = d * -(m[0][0] * c[1] - m[0][2] * c[13] + m[0][3] * c[14]);
	o[1][3] = d * (m[0][0] * c[0] - m[0][2] * c[15] + m[0][3] * c[16]);
	o[2][0] = d * (m[1][0] * c[4] - m[1][1] * c[10] + m[1][3] * c[12]);
	o[2][1] = d * -(m[0][0] * c[4] - m[0][1] * c[10] + m[0][3] * c[12]);
	o[2][2] = d * (m[0][0] * c[5] - m[0][1] * c[13] + m[0][3] * c[17]);
	o[2][3] = d * -(m[0][0] * c[6] - m[0][1] * c[15] + m[0][3] * c[18]);
	o[3][0] = d * -(m[1][0] * c[7] - m[1][1] * c[11] + m[1][2] * c[12]);
	o[3][1] = d * (m[0][0] * c[7] - m[0][1] * c[11] + m[0][2] * c[12]);
	o[3][2] = d * -(m[0][0] * c[8] - m[0][1] * c[14] + m[0][2] * c[17]);
	o[3][3] = d * (m[0][0] * c[9] - m[0][1] * c[16] + m[0][2] * c[18]);
}

t_mat4			*m4_inv(t_mat4 *m, t_mat4 *out)
{
	t_real d;
	t_real c[19];

	if (!m || !out)
		return (NULL);
	coefficient(m, c);
	d = m->r[0][0] *
			(m->r[1][1] * c[3] - m->r[1][2] * c[4] + m->r[1][3] * c[7])
		- m->r[0][1] *
			(m->r[1][0] * c[3] - m->r[1][2] * c[10] + m->r[1][3] * c[11])
		+ m->r[0][2] *
			(m->r[1][0] * c[4] - m->r[1][1] * c[10] + m->r[1][3] * c[12])
		- m->r[0][3] *
			(m->r[1][0] * c[7] - m->r[1][1] * c[11] + m->r[1][2] * c[12]);
	if (d == 0)
		return (NULL);
	d = 1 / d;
	inv_apply(m->r, c, out->r, d);
	return (out);
}

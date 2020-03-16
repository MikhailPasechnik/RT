/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:40:38 by bnesoi            #+#    #+#             */
/*   Updated: 2020/03/17 02:04:59 by bmahi            ###   ########.fr       */
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
			M44(out, r, c) = 0;
			while (k--)
				if (M44(a, r, k))
					M44(out, r, c) += M44(a, r, k) * M44(b, k, c);
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
	w = b->x * M44(a, 0, 3) +
		b->y * M44(a, 1, 3) +
		b->z * M44(a, 2, 3) + M44(a, 3, 3);
	out->x = (
		b->x * M44(a, 0, 0) +
		b->y * M44(a, 1, 0) +
		b->z * M44(a, 2, 0) + M44(a, 3, 0)) / w;
	out->y = (
		b->x * M44(a, 0, 1) +
		b->y * M44(a, 1, 1) +
		b->z * M44(a, 2, 1) + M44(a, 3, 1)) / w;
	out->z = (
		b->x * M44(a, 0, 2) +
		b->y * M44(a, 1, 2) +
		b->z * M44(a, 2, 2) + M44(a, 3, 2)) / w;
	return (out);
}

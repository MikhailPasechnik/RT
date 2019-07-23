/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:46:28 by bnesoi            #+#    #+#             */
/*   Updated: 2019/07/06 14:46:28 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgmath.h"

t_vec3	*v3_norm(t_vec3 *v, t_vec3 *out)
{
	t_real mag;

	if (!v || !out)
		return (NULL);
	mag = v3_mag(v);
	if (!mag)
		return (NULL);
	out->x = v->x / mag;
	out->y = v->y / mag;
	out->z = v->z / mag;
	return (out);
}

t_real	v3_mag(t_vec3 *v)
{
	return (sqrt(
			pow(v->x, 2) +
			pow(v->y, 2) +
			pow(v->z, 2)));
}

t_vec3	*v3_cross(t_vec3 *a, t_vec3 *b, t_vec3 *out)
{
	if (!a || !b || !out)
		return (NULL);
	out->x = a->y * b->z - a->z * b->y;
	out->y = a->z * b->x - a->x * b->z;
	out->z = a->x * b->y - a->y * b->x;
	return (out);
}

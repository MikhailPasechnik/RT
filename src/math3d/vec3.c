/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssheba <ssheba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:43:24 by bnesoi            #+#    #+#             */
/*   Updated: 2019/07/09 15:07:15 by ssheba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m3d.h"

t_m3d_vec3	*m3d_v3_add(t_m3d_vec3 *a, t_m3d_vec3 *b, t_m3d_vec3 *out)
{
	if (!a || !b || !out)
		return (NULL);
	out->x = a->x + b->x;
	out->y = a->y + b->y;
	out->z = a->z + b->z;
	return (out);
}

t_m3d_vec3	*m3d_v3_sub(t_m3d_vec3 *a, t_m3d_vec3 *b, t_m3d_vec3 *out)
{
	if (!a || !b || !out)
		return (NULL);
	out->x = a->x - b->x;
	out->y = a->y - b->y;
	out->z = a->z - b->z;
	return (out);
}

t_m3d_vec3	*m3d_v3_mull_s(t_m3d_vec3 *v, t_m3d_real s, t_m3d_vec3 *out)
{
	if (!v || !out)
		return (NULL);
	out->x = v->x * s;
	out->y = v->y * s;
	out->z = v->z * s;
	return (out);
}

t_m3d_vec3	*m3d_v3_copy(t_m3d_vec3 *v, t_m3d_vec3 *out)
{
	if (!v || !out)
		return (NULL);
	ft_memmove(out, v, sizeof(t_m3d_vec3));
	return (out);
}

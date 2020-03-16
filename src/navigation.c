/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 00:37:34 by bmahi             #+#    #+#             */
/*   Updated: 2020/03/17 00:38:18 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		nav_move_camera(t_cam *cam, t_vec3 *by)
{
	m4_translate(&cam->mtx, by);
}

void		nav_rotate_camera(t_cam *cam, t_vec3 *rot, t_vec3 *around)
{
	t_mat4	r;
	t_vec3	t;

	m4_extract_translation(&cam->mtx, &t);
	m4_set_rotation(&r, rot);
	m4_v3_mul(&r, &t, &t);
	cam->mtx = look_at(t, *around);
}

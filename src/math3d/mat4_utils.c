/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:37:28 by bnesoi            #+#    #+#             */
/*   Updated: 2019/07/06 14:37:36 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m3d.h"

t_mat4			*m4_identity(t_mat4 *m)
{
	int	i;
	int	j;

	if (!m)
		return (NULL);
	i = 4;
	while (i--)
	{
		j = 4;
		while (j--)
			m->r[i][j] = i == j;
	}
	return (m);
}

int				m4_is_identity(t_mat4 *m)
{
	int	i;
	int	j;

	i = 4;
	while (i--)
	{
		j = 4;
		while (j--)
		{
			if (R_ABS(m->r[i][j] - (t_real)(i == j)) > EPSILON)
				return (0);
		}
	}
	return (1);
}

t_mat4			*m4_copy(t_mat4 *m, t_mat4 *out)
{
	if (!m || !out)
		return (NULL);
	ft_memmove(out, m, sizeof(t_mat4));
	return (out);
}

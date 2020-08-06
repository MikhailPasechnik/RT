/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_vec_pick.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 17:11:10 by bmahi             #+#    #+#             */
/*   Updated: 2020/08/05 17:15:28 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "m3d.h"
#include "ft_printf.h"

unsigned int	gui_vec_pick(t_vec3 *vec, char *lbl, struct nk_context	*ctx)
{
	t_vec3	tmp;
	char	p[100];

	tmp = *vec;
	nk_layout_row_dynamic(ctx, 20, 1);
	nk_label(ctx, lbl, NK_TEXT_LEFT);
	nk_layout_row_dynamic(ctx, 25, 1);
	ft_sprintf(p, "%s:%c", lbl, 'X');
	tmp.x = nk_propertyf(ctx, p, -9999, tmp.x, 9999, 0.5f, 0.25f);
	ft_sprintf(p, "%s:%c", lbl, 'Y');
	tmp.y = nk_propertyf(ctx, p, -9999, tmp.y, 9999, 0.5f, 0.25f);
	ft_sprintf(p, "%s:%c", lbl, 'Z');
	tmp.z = nk_propertyf(ctx, p, -9999, tmp.z, 9999, 0.5f, 0.25f);
	if (!CMP_VEC((&tmp), vec))
	{
		*vec = tmp;
		return (1);
	}
	return (0);
}

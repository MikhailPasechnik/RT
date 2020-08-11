/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_single_pick.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 17:11:06 by bmahi             #+#    #+#             */
/*   Updated: 2020/08/05 17:13:11 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "m3d.h"

unsigned int	gui_single_pick(t_real *v, char *lbl, struct nk_context	*ctx)
{
	float	tmp;

	tmp = *v;
	nk_layout_row_dynamic(ctx, 20, 1);
	nk_label(ctx, "", NK_TEXT_LEFT);
	nk_layout_row_dynamic(ctx, 25, 1);
	tmp = nk_propertyf(ctx, lbl, 0, tmp, 9999, 0.5f, 0.25f);
	if (tmp != *v)
	{
		*v = tmp;
		return (1);
	}
	return (0);
}

unsigned int	gui_isingle_pick(int *v, char *lbl, struct nk_context *ctx)
{
	int	tmp;

	tmp = *v;
	nk_layout_row_dynamic(ctx, 20, 1);
	nk_label(ctx, "", NK_TEXT_LEFT);
	nk_layout_row_dynamic(ctx, 25, 1);
	tmp =  nk_propertyi(ctx, lbl, 0, tmp, 9999, 1, 1);
	if (tmp != *v)
	{
		*v = tmp;
		return (1);
	}
	return (0);
}

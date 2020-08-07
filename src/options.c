/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 23:02:59 by bmahi             #+#    #+#             */
/*   Updated: 2020/08/02 19:53:28 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_options(t_options *op)
{
	op->height = RT_WIN_HEIGHT;
	op->width = RT_WIN_WIDTH;
	op->selection = -1;
	op->ref_depth = 4;
	op->background_color = VEC(44 / 255.0, 44 / 255.0, 44 / 255.0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2020/02/17 23:01:22 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

size_t	rt_tab_len(char **tab)
{
	size_t	len;

	len = 0;
	while (tab && tab[len])
		len++;
	return (len);
}

void	*rt_tab_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

//void	*rt_set_rect(SDL_Rect *rect, int x, int y, int w, int h)
//{
//	if (rect)
//	{
//		rect->x = x;
//		rect->y = y;
//		rect->w = w;
//		rect->h = h;
//	}
//}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2020/03/17 00:55:29 by bmahi            ###   ########.fr       */
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

t_color	get_surface_pixel(SDL_Surface *surface, size_t x, size_t y)
{
	Uint32		*p;
	Uint8		r;
	Uint8		g;
	Uint8		b;
	Uint8		a;

	p = (Uint32 *)surface->pixels + y * surface->pitch + x *
			surface->format->BitsPerPixel;
	SDL_GetRGBA(*p, surface->format, &r, &g, &b, &a);
	return (COLOR(r / 255.0, g / 255.0, b / 255., a / 255.0));
}

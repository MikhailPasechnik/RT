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

#include <time.h>
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

void	screen_shot_name(char name[150])
{
	time_t		now;
	struct tm	*time_struct;
	char		time_str[100];

	now = time(NULL);
	time_struct = localtime(&now);
	strftime(time_str, 99, "%d %m %Y %H:%M:%S", time_struct);
	ft_sprintf(name, "RTv1 %s", time_str);
}

int		screen_shot(t_app *app)
{
	t_tx_buffer	*current;
	void		*pixels;
	int 		pitch;
	int 		result;
	char		name[150];

	if (app->render_buffer == RT_K_COLOR_ARG)
		current = &app->ren.color_buf;
	else if (app->render_buffer == RT_K_NORMA_ARG)
		current = &app->ren.normal_buf;
	else if (app->render_buffer == RT_K_DEPTH_ARG)
		current = &app->ren.depth_buf;
	else
		return (0);
	screen_shot_name(name);
	SDL_LockTexture(current->host, NULL, &pixels, &pitch);
	result = save_image(name, pixels, app->op.width, app->op.height);
	SDL_UnlockTexture(current->host);
	if (!result)
		ft_fprintf(2, "Failed to save Screen shot!\n");
	else
		ft_printf("Screen shot saved to: %s.pgm\n", name);
	return (result);
}

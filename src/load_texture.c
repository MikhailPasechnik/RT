/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvernius <cvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 19:23:36 by cvernius          #+#    #+#             */
/*   Updated: 2020/08/04 18:35:48 by cvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int		check_pixmap(t_load_text load_t)
{
	if (!load_t.pixmap)
		exit(13); // texture_load error
	return (1);
}

int		check_nchannels(t_load_text load_t)
{
	if (load_t.nchannels != 4)
	{
		stbi_image_free(load_t.pixmap);
		exit(13); //texture_channels
	}
	return (1);
}

void	init_one_texture(t_load_text load_t, t_texture *t)
{
	t->cnt = load_t.w / load_t.h;
	t->size = load_t.w / t->cnt;
	t->texture = (int*)malloc(sizeof(int) * load_t.w * load_t.h);
	(t->texture == NULL ? exit(0) : 1);
}

int		load_texture(char *filename, t_texture *t)
{
	t_load_text	load_t;
	t_pix		pix;
	t_color		c;

	pix = (t_pix){0, 0};
	load_t.pixmap = stbi_load(filename, &load_t.w, &load_t.h,
													&load_t.nchannels, 0);
	if (!check_pixmap(load_t) && !check_nchannels(load_t))
		return (0);
	init_one_texture(load_t, t);
	while (pix.y < load_t.h)
	{
		pix.x = 0;
		while (pix.x < load_t.w)
		{
			c.r = (int)load_t.pixmap[(pix.x + pix.y * load_t.w) * 4 + 0] / 255.0;
			c.g = (int)load_t.pixmap[(pix.x + pix.y * load_t.w) * 4 + 1] / 255.0;
			c.b = (int)load_t.pixmap[(pix.x + pix.y * load_t.w) * 4 + 2] / 255.0;
			pix.x++;
		}
		pix.y++;
	}
	stbi_image_free(load_t.pixmap);
	return (1);
}

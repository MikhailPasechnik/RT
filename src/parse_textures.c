/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 22:29:50 by bmahi             #+#    #+#             */
/*   Updated: 2020/08/10 17:33:22 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "stb_image.h"

static t_uint	get_texture_offset(t_list *last)
{
	t_tx_info	*prev;

	prev = last ? last->content : NULL;
	if (prev)
		return (prev->buffer_offset +
			sizeof(unsigned char) * prev->w * prev->h * 4);
		return (0);
}

static int		instance_tx(char *str, void *id, t_app *app)
{
	int		i;
	t_list	*it;

	it = app->tx_src_list;
	i = (int)app->op.tex_count - 1;
	while (it)
	{
		*(t_int *)id = i;
		if (!ft_strcmp((char *)it->content, str))
			return (1);
		i--;
		it = it->next;
	}
	return (0);
}

static int		load_tx(char *path, t_tx_info *info, t_list *tx, t_app *app)
{
	tx->content = stbi_load(path, &info->w, &info->h, &info->channels, 4);
	if ((app->parse_error |= (unsigned)(tx->content == NULL)))
	{
		free(tx);
		return (0);
	}
	tx->content_size = sizeof(unsigned char) * info->w * info->h * 4;
	info->buffer_offset = get_texture_offset(app->tx_info_list);
	return (1);
}

void			parse_texture(char *str, void *id, t_app *app)
{
	t_list		*tx;
	t_tx_info	info;
	t_list		*info_l;
	t_list		*src;

	while (ft_iswhitespace(*str))
		str++;
	if (instance_tx(str, id, app))
		return ;
	tx = ft_lstnew(NULL, 0);
	if ((app->parse_error |= (unsigned)(tx == NULL)))
		return ;
	if (!load_tx(str, &info, tx, app))
		return ;
	ft_lstadd(&app->tx_list, tx);
	info_l = ft_lstnew(&info, sizeof(info));
	if ((app->parse_error |= (unsigned)(info_l == NULL)))
		return ;
	ft_lstadd(&app->tx_info_list, info_l);
	src = ft_lstnew(str, sizeof(char) * (ft_strlen(str) + 1));
	if ((app->parse_error |= (unsigned)(src == NULL)))
		return ;
	ft_lstadd(&app->tx_src_list, src);
	*(int *)id = app->op.tex_count++;
}

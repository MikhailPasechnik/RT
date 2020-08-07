/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:55:25 by bnesoi            #+#    #+#             */
/*   Updated: 2020/08/02 16:47:14 by bmahi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

size_t	list_size(t_list *lst)
{
	size_t		size;

	size = 0;
	while (lst)
	{
		size += lst->content_size;
		lst = lst->next;
	}
	return (size);
}

void	file_name(char name[150])
{
	time_t		now;
	struct tm	*time_struct;
	char		time_str[100];

	now = time(NULL);
	time_struct = localtime(&now);
	strftime(time_str, 99, "%d %m %Y %H:%M:%S", time_struct);
	ft_sprintf(name, "RT %s", time_str);
}

int		screen_shot(t_app *app)
{
	t_tx_buffer	*current;
	void		*pixels;
	int			pitch;
	int			result;
	char		name[150];

	if (app->render_buffer == RT_K_COLOR_ARG)
		current = &app->ren.color_buf;
	else if (app->render_buffer == RT_K_NORMA_ARG)
		current = &app->ren.normal_buf;
	else if (app->render_buffer == RT_K_DEPTH_ARG)
		current = &app->ren.depth_buf;
	else
		return (0);
	file_name(name);
	SDL_LockTexture(current->host, NULL, &pixels, &pitch);
	result = save_image(name, pixels, app->op.width, app->op.height);
	SDL_UnlockTexture(current->host);
	if (!result)
		ft_fprintf(2, "Failed to save Screen shot!\n");
	else
		ft_printf("Screen shot saved to: %s.pgm\n", name);
	return (result);
}

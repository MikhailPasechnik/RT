/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:51:04 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:51:11 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new;

	if ((new = (t_list *)ft_memalloc(sizeof(*new))) == NULL)
		return (NULL);
	new->content_size = 0;
	new->content = 0;
	new->next = NULL;
	if (content)
	{
		new->content_size = content_size;
		if ((new->content = ft_memalloc(content_size)) == NULL)
		{
			ft_memdel((void **)&new);
			return (NULL);
		}
		ft_memmove(new->content, content, content_size);
	}
	return (new);
}

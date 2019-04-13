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

	if ((new = (t_list *)malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->next = NULL;
	new->content_size = content ? content_size : 0;
	new->content = content ? (void *)content : NULL;
	return (new);
}

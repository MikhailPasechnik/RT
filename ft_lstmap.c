/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:50:22 by bnesoi            #+#    #+#             */
/*   Updated: 2019/05/10 14:35:53 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		del_lst(void *c, size_t s)
{
	(void)s;
	ft_memdel(&c);
}

static void		*free_lst(t_list *first)
{
	ft_lstdel(&first, del_lst);
	return (NULL);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*current;
	t_list	*first;

	if (!lst || !f || !(current = f(lst)))
		return (NULL);
	if((current = ft_lstnew(current->content, current->content_size)) == NULL)
		return (NULL);
	first = current;
	lst = lst->next;
	while (lst && (current->next = f(lst)))
	{
		if ((current->next = ft_lstnew(
				current->next->content, current->next->content_size
				)) == NULL)
			return (free_lst(first));
		current = current->next;
		lst = lst->next;
	}
	return (first);
}

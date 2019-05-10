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

static t_list	*cpy_list(t_list *lst)
{
	return (lst ? ft_lstnew(lst->content, lst->content_size) : NULL);
}

static void		free_lst(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head->next;
		ft_memdel(&head);
		head = tmp;
	}
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*new;
	t_list	*head;

	head = NULL;
	new = NULL;
	while (f && lst)
	{
		if ((tmp = cpy_list(f(lst))) == NULL)
		{
			free_lst(head);
			return (NULL);
		}
		else if (!new)
			new = tmp;
		else
		{
			new->next = tmp;
			new = new->next;
		}
		if (!head)
			head = new;
		lst = lst->next;
	}
	return (head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:50:22 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:50:58 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*new;
	t_list	*head;

	head = NULL;
	new = NULL;
	while (lst)
	{
		if ((tmp = f(lst)) == NULL)
			return (NULL);
		else if (!new)
			new = tmp;
		else
		{
			new = new->next;
			new->next = tmp;
		}
		if (!head)
			head = new;
		lst = lst->next;
	}
	return (head);
}

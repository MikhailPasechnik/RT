/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:49:49 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:50:07 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *lst, const void *ref,
			int (*cmp)(const void *, const void *))
{
	while (cmp && lst)
	{
		if (cmp(lst->content, ref) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

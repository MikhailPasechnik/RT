/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:10:18 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:10:26 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_queue_del(t_queue **queue, void (*del)(void *, size_t))
{
	if (queue && *queue)
		ft_lstdel(&(*queue)->front, del);
	if (queue)
	{
		ft_memdel((void**)queue);
		*queue = NULL;
	}
}

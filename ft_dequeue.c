/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dequeue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:39:00 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:41:10 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_dequeue(t_queue *queue)
{
	t_list	*item;

	item = queue->front;
	if (item == NULL)
		return (NULL);
	queue->front = item->next;
	item->next = NULL;
	if (queue->front == NULL)
		queue->rear = NULL;
	return (item);
}

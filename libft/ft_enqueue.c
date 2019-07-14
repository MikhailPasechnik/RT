/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enqueue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:45:49 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:45:54 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_enqueue(t_queue *queue, t_list *item)
{
	if (queue->rear == NULL)
	{
		queue->rear = item;
		queue->front = item;
	}
	else
	{
		queue->rear->next = item;
		queue->rear = item;
	}
}

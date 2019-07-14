/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:10:30 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:10:32 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_queue		*ft_queue_new(void)
{
	t_queue	*queue;

	if ((queue = ft_memalloc(sizeof(*queue))) == NULL)
		return (NULL);
	queue->rear = NULL;
	queue->front = NULL;
	return (queue);
}

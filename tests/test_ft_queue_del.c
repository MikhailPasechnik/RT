/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_queue_del.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:10:13 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void    	queue_del(void *c, size_t s)
{
	memset(c, '!', s);
	(void)c;
	(void)s;
}

int				main(void)
{
	t_queue *q;
	q = malloc(sizeof(*q));
	t_list  *l;
	l = malloc(sizeof(*l));
	char c[] = ".....";
	*l = (t_list){c, 4, NULL};
	q->rear = l;
	q->front = l;
	ft_queue_del(&q, queue_del);
	OK(q == NULL);
	IS(c, "!!!!.");
	return (0);
}

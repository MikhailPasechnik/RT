/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_queue_del.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 10:28:29 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	queue_del(void *c, size_t s)
{
	ft_memset(c, '!', s);
	(void)c;
	(void)s;
}

int			main(void)
{
	t_queue	*q;
	t_list	*l;
	char	c[6];

	q = ft_memalloc(sizeof(*q));
	l = ft_memalloc(sizeof(*l));
	ft_strcpy(c, ".....");
	*l = (t_list){c, 4, NULL};
	q->rear = l;
	q->front = l;
	ft_queue_del(&q, queue_del);
	FT_OK(q == NULL);
	FT_IS(c, "!!!!.");
	return (0);
}

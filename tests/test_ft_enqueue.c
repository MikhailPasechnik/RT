/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_enqueue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:10:13 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	t_list  l4 = {"4", 1, NULL};
	t_list  l3 = {"3", 1, NULL};
	t_list  l2 = {"2", 1, NULL};
	t_list  l1 = {"1", 1, NULL};
	t_queue q = {NULL, NULL};
	ft_enqueue(&q, &l1);
	ft_enqueue(&q, &l2);
	ft_enqueue(&q, &l3);
	ft_enqueue(&q, &l4);
	IS(ft_dequeue(&q)->content, "1");
	IS(ft_dequeue(&q)->content, "2");
	IS(ft_dequeue(&q)->content, "3");
	IS(ft_dequeue(&q)->content, "4");
	OK(q.front == NULL);
	OK(q.rear == NULL);
	return (0);
}

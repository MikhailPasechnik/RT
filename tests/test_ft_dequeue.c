/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_dequeue.c                                  :+:      :+:    :+:   */
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
	t_list  l2 = {"2", 1, NULL};
	t_list  l1 = {"1", 1, &l2};
	t_queue q = {&l1, &l2};
	t_list  dq = *ft_dequeue(&q);
	FT_IS(dq.content, "1");
	FT_IS(q.rear->content, "2");
	FT_IS(q.front->content, "2");
	dq = *ft_dequeue(&q);
	FT_IS(dq.content, "2");
	FT_OK(q.rear == NULL);
	FT_OK(q.front == NULL);
	return (0);
}

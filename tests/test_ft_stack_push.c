/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_stack_push.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 10:32:17 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	t_list	l4;
	t_list	l3;
	t_list	l2;
	t_list	l1;
	t_stack	s;

	l4 = (t_list){"4", 1, NULL};
	l3 = (t_list){"3", 1, NULL};
	l2 = (t_list){"2", 1, NULL};
	l1 = (t_list){"1", 1, NULL};
	s = (t_stack){NULL};
	ft_stack_push(&s, &l1);
	ft_stack_push(&s, &l2);
	ft_stack_push(&s, &l3);
	ft_stack_push(&s, &l4);
	FT_IS(s.top->content, "4");
	FT_IS(s.top->next->content, "3");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_stack_push.c                               :+:      :+:    :+:   */
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
	t_stack s = {NULL};
	ft_stack_push(&s, &l1);
	ft_stack_push(&s, &l2);
	ft_stack_push(&s, &l3);
	ft_stack_push(&s, &l4);
	FT_IS(s.top->content, "4");
	FT_IS(s.top->next->content, "3");
	return (0);
}

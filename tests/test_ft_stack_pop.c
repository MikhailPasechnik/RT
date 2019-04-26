/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_stack_pop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 10:31:12 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	t_list	l2;
	t_list	l1;
	t_stack	s;

	l2 = (t_list){"2", 1, NULL};
	l1 = (t_list){"1", 1, &l2};
	s = (t_stack){&l1};
	FT_IS(ft_stack_pop(&s)->content, "1");
	FT_IS(ft_stack_pop(&s)->content, "2");
	FT_OK(!s.top);
	return (0);
}

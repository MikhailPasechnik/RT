/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_stack_del.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 10:29:57 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	stack_del(void *c, size_t s)
{
	ft_memset(c, '!', s);
	(void)c;
	(void)s;
}

int			main(void)
{
	t_stack *s;
	t_list	*l;
	char	c[6];

	s = ft_memalloc(sizeof(t_stack));
	l = ft_memalloc(sizeof(t_list));
	ft_strcpy(c, ".....");
	*l = (t_list){c, 4, NULL};
	s->top = l;
	ft_stack_del(&s, stack_del);
	FT_OK(s == NULL);
	FT_IS(c, "!!!!.");
	return (0);
}

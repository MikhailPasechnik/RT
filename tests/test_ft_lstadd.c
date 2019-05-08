/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_lstadd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/05/08 20:06:49 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void		del(void *c, size_t s)
{
	(void)c;
	(void)(s);
}

int				main(void)
{
	t_list	*l;
	t_list	*t;
	int		i;

	l = ft_lstnew("1", 2);
	ft_lstadd(&l, ft_lstnew("2", 2));
	ft_lstadd(&l, ft_lstnew("3", 2));
	ft_lstadd(&l, ft_lstnew("4", 2));
	t = l;
	i = 4;
	while (l)
	{
		FT_IS(l->content, ft_itoa(i));
		l = l->next;
		i--;
	}
	ft_lstdel(&t, del);
	return (0);
}

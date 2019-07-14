/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_lstiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 10:20:51 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void		ft_iter(t_list *elem)
{
	char	*c;

	c = ft_memset(ft_strnew(elem->content_size), '.', elem->content_size);
	*elem = (t_list){(void *)c, elem->content_size, elem->next};
}

static void		ft_iter_del(t_list *elem)
{
	ft_strdel((char **)&elem->content);
}

int				main(void)
{
	t_list	d;
	t_list	c;
	t_list	b;
	t_list	a;

	d = (t_list){"444\0", 4, NULL};
	c = (t_list){"33\0", 3, &d};
	b = (t_list){"2\0", 2, &c};
	a = (t_list){"\0", 1, &b};
	ft_lstiter(&a, NULL);
	ft_lstiter(NULL, ft_iter);
	ft_lstiter(&a, ft_iter);
	FT_IS(a.content, ".");
	FT_IS(a.next->content, "..");
	FT_IS(a.next->next->content, "...");
	FT_IS(a.next->next->next->content, "....");
	ft_lstiter(&a, ft_iter_del);
	return (0);
}

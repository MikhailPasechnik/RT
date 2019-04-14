/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_lstmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:10:13 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static t_list	*ft_map(t_list *elem)
{
	t_list	*e;
	size_t	i;
	char	*c;

	i = 0;
	ft_strcpy((c = ft_strnew(elem->content_size)), elem->content);
	e = ft_lstnew(c, elem->content_size);
	if (!e)
		return (0);
	while (i < e->content_size)
	{
		((char *)e->content)[i] = '.';
		i++;
	}
	return (e);
}

static void		ft_check_res(t_list *res)
{
	IS(res->content, ".");
	IS(res->next->content, "..");
	IS(res->next->next->content, "...");
	IS(res->next->next->next->content, "....");
}

static void		ft_del_res(void *c, size_t len)
{
	(void)len;
	ft_strdel((char **)&c);
}

int				main(void)
{
	t_list	d;
	t_list	c;
	t_list	b;
	t_list	a;
	t_list  *res;

	d = (t_list){"444\0", 4, NULL};
	c = (t_list){"33\0", 3, &d};
	b = (t_list){"2\0", 2, &c};
	a = (t_list){"\0", 1, &b};
	res = ft_lstmap(&a, NULL);
	OK(res == NULL);
	res = ft_lstmap(NULL, ft_map);
	OK(res == NULL);
	res = ft_lstmap(&a, ft_map);
	ft_check_res(res);
	ft_lstdel(&res, ft_del_res);
	return (0);
}

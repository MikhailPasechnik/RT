/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_lstmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 10:21:48 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static t_list	*ft_map(t_list *elem)
{
	size_t	i;
	char	*c;

	i = 0;
	ft_strcpy((c = ft_strnew(elem->content_size)), elem->content);
	elem->content = c;
	while (i < elem->content_size - 1)
	{
		((char *)elem->content)[i] = '.';
		i++;
	}
	return (elem);
}

static void		ft_del_res(void *c, size_t len)
{
	(void)len;
	ft_strdel((char **)&c);
}

static void		ft_del_src(t_list *e)
{
	ft_strdel((char **)&e->content);
}

int				main(void)
{
	t_list	d;
	t_list	c;
	t_list	b;
	t_list	a;
	t_list	*res;

	d = (t_list){"444\0", 5, NULL};
	c = (t_list){"33\0", 4, &d};
	b = (t_list){"2\0", 3, &c};
	a = (t_list){"\0", 2, &b};
	res = ft_lstmap(&a, NULL);
	FT_OK(res == NULL);
	res = ft_lstmap(NULL, ft_map);
	FT_OK(res == NULL);
	res = ft_lstmap(&a, ft_map);
	FT_IS(res->content, ".");
	FT_IS(res->next->content, "..");
	FT_IS(res->next->next->content, "...");
	FT_IS(res->next->next->next->content, "....");
	ft_lstiter(&a, ft_del_src);
	ft_lstdel(&res, ft_del_res);
	return (0);
}

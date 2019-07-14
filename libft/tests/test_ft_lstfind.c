/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_lstfind.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/05/08 20:23:13 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void		del(void *c, size_t s)
{
	(void)c;
	(void)(s);
}

static int		cmp(const void *a, const void *b)
{
	return (ft_strcmp(a, b));
}

int				main(void)
{
	t_list	*l;

	l = ft_lstnew("1", 2);
	ft_lstadd(&l, ft_lstnew("2", 2));
	ft_lstadd(&l, ft_lstnew("3", 2));
	ft_lstadd(&l, ft_lstnew("4", 2));
	FT_OK(ft_lstfind(l, "0", cmp) == NULL);
	FT_IS(ft_lstfind(l, "1", cmp)->content, "1");
	FT_IS(ft_lstfind(l, "3", cmp)->content, "3");
	FT_IS(ft_lstfind(l, "4", cmp)->content, "4");
	ft_lstdel(&l, del);
	return (0);
}

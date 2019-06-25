/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_lstdel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/05/08 20:18:52 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void		del(void *c, size_t s)
{
	FT_OK(((char *)c)[0] == '1');
	FT_OK(s == 2);
	ft_strdel((char **)&c);
}

int				main(void)
{
	t_list	*l;

	l = ft_lstnew("1", 2);
	ft_lstadd(&l, ft_lstnew("1", 2));
	ft_lstadd(&l, ft_lstnew("1", 2));
	ft_lstadd(&l, ft_lstnew("1", 2));
	ft_lstdel(&l, del);
	FT_OK(l == NULL);
	return (0);
}

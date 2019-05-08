/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_lstnew.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 10:21:57 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void		del(void *c, size_t s)
{
}

int				main(void)
{
	t_list	*l;

	l = ft_lstnew("abc", 4);
	FT_IS(l->content, "abc");
	FT_OK(l->content_size == 4);
	FT_OK(l->next == NULL);
	ft_lstdel(&l, del);
	return (0);
}

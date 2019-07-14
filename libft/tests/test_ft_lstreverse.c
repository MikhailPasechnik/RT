/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_lstreverse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 10:23:03 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	t_list	*l;
	t_list	c;
	t_list	b;
	t_list	a;

	c = (t_list){"c", 2, NULL};
	b = (t_list){"b", 2, &c};
	a = (t_list){"a", 2, &b};
	l = &a;
	ft_lstreverse(&l);
	FT_IS(l->content, "c");
	FT_IS(l->next->content, "b");
	FT_IS(l->next->next->content, "a");
	return (0);
}

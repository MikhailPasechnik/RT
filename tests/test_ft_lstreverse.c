/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_lstreverse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:10:13 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	t_list *l;
	t_list c = {"c", 2, NULL};
	t_list b = {"b", 2, &c};
	t_list a = {"a", 2, &b};
	l = &a;
	ft_lstreverse(&l);
	FT_TAP_IS(l->content, "c");
	FT_TAP_IS(l->next->content, "b");
	FT_TAP_IS(l->next->next->content, "a");
	return (0);
}

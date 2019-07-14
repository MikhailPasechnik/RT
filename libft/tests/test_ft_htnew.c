/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_htnew.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 10:13:31 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int				main(void)
{
	t_htable	*t;

	t = ft_htnew(100, NULL, NULL, NULL);
	FT_OK(t->size == 100);
	FT_OK(t->bins != NULL);
	FT_OK(t->bins[0] == NULL);
	FT_OK(t->bins[99] == NULL);
	ft_htdel(&t);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_htget.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 10:13:28 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int			func_key_cmp(void *a, void *b)
{
	return (ft_strcmp(a, b));
}

static size_t		func_key_hash(void *key, size_t size)
{
	return (ft_strhash(key, size));
}

int					main(void)
{
	t_htable	*t;

	t = ft_htnew(100, func_key_cmp, func_key_hash, NULL);
	ft_htset(t, "a", "A");
	FT_IS(ft_htget(t, "a"), "A");
	ft_htset(t, "a", "N");
	FT_IS(ft_htget(t, "a"), "N");
	ft_htdel(&t);
	return (0);
}

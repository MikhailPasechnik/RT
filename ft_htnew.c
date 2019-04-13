/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htnew.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:22:23 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:45:36 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_htable	*ft_htnew(size_t size,
		int (*func_key_cmp)(void *, void *),
		size_t (*func_key_hash)(void *, size_t),
		void (*func_key_value_del)(void *, void *))
{
	t_htable	*ht;

	if ((ht = ft_memalloc(sizeof(*ht))) == NULL)
		return (NULL);
	if ((ht->bins = ft_memalloc(sizeof(*ht->bins) * size)) == NULL)
	{
		ft_memdel((void **)&ht);
		return (NULL);
	}
	ht->size = size;
	ht->func_key_cmp = func_key_cmp;
	ht->func_key_hash = func_key_hash;
	ht->func_key_value_del = func_key_value_del;
	return (ht);
}

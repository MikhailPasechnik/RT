/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htget.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:45:58 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:46:19 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_htget(t_htable *ht, void *key)
{
	t_htentry	*entry;

	if (ht && key)
	{
		entry = ht->bins[ht->func_key_hash(key, ht->size)];
		while (entry)
		{
			if (ht->func_key_cmp(entry->key, key) == 0)
				return (entry->value);
			entry = entry->next;
		}
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htdel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:25:37 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:45:43 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_htdel(t_htable **ht)
{
	t_htentry	*tmp;
	size_t		i;

	if (ht)
	{
		i = 0;
		while (i < (*ht)->size)
		{
			while ((*ht)->bins[i])
			{
				tmp = (*ht)->bins[i]->next;
				if ((*ht)->func_key_value_del)
					(*ht)->func_key_value_del((*ht)->bins[i]->key,
						(*ht)->bins[i]->value);
				ft_memdel((void **)&(*ht)->bins[i]);
				(*ht)->bins[i] = tmp;
			}
			i++;
		}
		ft_memdel((void **)&(*ht)->bins);
		ft_memdel((void **)ht);
		*ht = NULL;
	}
}

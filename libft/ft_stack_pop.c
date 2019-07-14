/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:11:00 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:11:01 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_stack_pop(t_stack *stack)
{
	t_list	*item;

	item = stack->top;
	if (item != NULL)
	{
		stack->top = item->next;
		item->next = NULL;
	}
	return (item);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:10:38 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:10:48 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_stack_del(t_stack **stack, void (*del)(void *, size_t))
{
	if (stack && *stack)
		ft_lstdel(&(*stack)->top, del);
	if (stack)
	{
		ft_memdel((void**)stack);
		*stack = NULL;
	}
}

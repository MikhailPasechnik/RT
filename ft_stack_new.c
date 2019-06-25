/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:10:55 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:10:56 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack		*ft_stack_new(void)
{
	t_stack	*stack;

	if ((stack = ft_memalloc(sizeof(stack))) == NULL)
		return (NULL);
	stack->top = NULL;
	return (stack);
}

#include "libft.h"

void	ft_stack_push(t_stack *stack, t_list *new)
{
	new->next = stack->top;
	stack->top = new;
}

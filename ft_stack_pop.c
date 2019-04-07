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

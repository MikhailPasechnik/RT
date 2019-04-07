#include "libft.h"

void	ft_stack_del(t_stack *stack, void (*del)(void *, size_t))
{
	ft_lstdel(&stack->top, del);
	free(stack);
}

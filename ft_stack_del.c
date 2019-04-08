#include "libft.h"

void	ft_stack_del(t_stack **stack, void (*del)(void *, size_t))
{
    if(stack && *stack)
	    ft_lstdel(&(*stack)->top, del);

	if(stack)
	{
        free(*stack);
        *stack = NULL;
    }
}

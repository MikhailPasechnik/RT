#include "libft.h"

t_stack		*ft_stack_new(void)
{
	t_stack	*stack;

	if ((stack = malloc(sizeof(stack))) == NULL)
		return (NULL);
	stack->top = NULL;
	return (stack);
}

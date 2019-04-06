#include "libft.h"

t_stack		*ft_stack_init(void)
{
	t_stack	*stack;

	if ((stack = malloc(sizeof(stack))) == NULL)
		return (NULL);
	stack->top = NULL;
	return (stack);
}

void		ft_stack_push(t_stack *stack, t_list *new)
{
	new->next = stack->top;
	stack->top = new;
}

t_list		*ft_stack_pop(t_stack *stack)
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
void		ft_stack_del(t_stack *stack, void (*del)(void *, size_t))
{
	ft_lstdel(&stack->top, del);
	free(stack);
}

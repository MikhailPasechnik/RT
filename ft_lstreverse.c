#include "libft.h"

void	ft_lstreverse(t_list **alst)
{
	t_list *third;
	t_list *second;
	t_list *first;

	if (!alst || !(first = *alst) || !(first->next))
		return ;
	second = first->next;
	third = second->next;
	first->next = 0;
	second->next = first;
	while (third)
	{
		first = second;
		second = third;
		third = third->next;
		second->next = first;
	}
	*alst = second;
}

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t)) {
	t_list	*tmp;
	if (*alst)
	{
		tmp = (*alst)->next;
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = tmp;
	}
}

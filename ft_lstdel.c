#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t)) {
    t_list *tmp;

    if (alst && del)
    {
        while (*alst) {
            tmp = (*alst)->next;
            ft_lstdelone(alst, del);
            *alst = tmp;
        }
    }
}

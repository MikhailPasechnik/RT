#include "libft.h"

t_list  *ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
    t_list  *tmp;
    t_list  *new;
    t_list  *head;

    head = NULL;
    new = NULL;
    while(lst)
    {
        if ((tmp = f(lst)) == NULL)
            return (NULL);
        else if (!new)
            new = tmp;
        else
            new = new->next = tmp;
        if (!head)
            head = new;
        lst = lst->next;
    }
    return (head);
}

#include "libft.h"

t_list  *ft_lstfind(t_list *lst, const void *ref,
            int (*cmp)(const void *, const void *))
{
    while(cmp && lst)
    {
        if (cmp(lst->content, ref)== 0)
            return (lst);
        lst = lst->next;
    }
    return (NULL);
}

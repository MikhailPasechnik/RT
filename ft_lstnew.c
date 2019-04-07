#include "libft.h"

t_list			*ft_lstnew(void const *content, size_t content_size)
{
    t_list *new;

    if ((new = (t_list *)malloc(sizeof(*new))) == NULL)
        return (NULL);
    new->next = NULL;
    new->content_size = content ? content_size : 0;
    new->content = content ? (void *)content : NULL;
    return (new);
}
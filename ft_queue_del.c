#include "libft.h"

void	ft_queue_del(t_queue **queue, void (*del)(void *, size_t))
{
    if (queue && *queue)
	    ft_lstdel(&(*queue)->front, del);
    if(queue)
    {
        free(*queue);
        *queue = NULL;
    }
}

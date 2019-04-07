#include "libft.h"

void		ft_queue_del(t_queue *queue, void (*del)(void *, size_t))
{
	ft_lstdel(&queue->front, del);
	free(queue);
}

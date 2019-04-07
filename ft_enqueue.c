#include "libft.h"

void		ft_enqueue(t_queue *queue, t_list *item)
{
	if (queue->rear == NULL)
	{
		queue->rear = item;
		queue->front = item;
	}
	else
	{
		queue->rear->next = item;
		queue->rear = item;
	}
}

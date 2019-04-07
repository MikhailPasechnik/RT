#include "libft.h"

t_list		*ft_dequeue(t_queue *queue)
{
	t_list	*item;

	item = queue->front;
	if (item == NULL)
		return (NULL);
	queue->front = item->next;
	item->next = NULL;
	if (queue->front == NULL)
		queue->rear = NULL;
	return (item);
}

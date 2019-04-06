#include "libft.h"

t_queue		*ft_queue_init(void)
{
	t_queue	*queue;

	if ((queue = malloc(sizeof(queue))) == NULL)
		return (NULL);
	queue->rear = NULL;
	queue->front = NULL;
	return (queue);
}

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

void		ft_queue_del(t_queue *queue, void (*del)(void *, size_t))
{
	ft_lstdel(&queue->front, del);
	free(queue);
}

#include "libft.h"

t_queue		*ft_queue_new(void)
{
	t_queue	*queue;

	if ((queue = malloc(sizeof(queue))) == NULL)
		return (NULL);
	queue->rear = NULL;
	queue->front = NULL;
	return (queue);
}

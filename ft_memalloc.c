#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *mem;

	if ((mem = (void *)malloc(size)) == NULL)
		return (NULL);
	return (ft_memset(mem, 0, size));
}

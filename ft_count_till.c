#include "libft.h"

size_t	ft_count_till(const char *str, int dir, size_t start,
						int (*f)(int), int cmp)
{
	size_t	count;

	count = 0;
	while (start && str[start] && f(str[start]) == cmp)
	{
		start+=dir;
		count++;
	}
	return (count);
}

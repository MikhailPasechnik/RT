#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*new;

	if ((new = ft_memalloc(sizeof(*new) * (size + 1))) == NULL)
		return (NULL);
	return (ft_memset(new, '\0', size + 1));
}

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if ((sub = ft_strnew(len)) == NULL)
		return (NULL);
	return ft_memmove(sub, &s[start], len);
}


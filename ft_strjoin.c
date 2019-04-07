#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) - 1;
	if ((new = ft_strnew(len)) == NULL)
		return (NULL);
	ft_memset(new, '\0', len + 1);
	ft_strcat(new, s1);
	ft_strcat(new, s2);
	return (new);
}

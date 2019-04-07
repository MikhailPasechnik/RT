#include "libft.h"

char			*ft_strtrim(char const *s)
{
	size_t	len;
	size_t	start;
	size_t	end;
	char	*new;

	len = ft_strlen(s);
	end = ft_count_till(s, -1, len-1, ft_iswhitespace, 0);
	start = ft_count_till(s, 1, 0, ft_iswhitespace, 0);
	if (start >= end)
		return ft_strnew(0);
	else if ((new = ft_strnew(end - start)) == NULL)
		return (NULL);
	ft_strncpy(new, &s[start], end - start);
	new[end - start] = '\0';
	return new;
}

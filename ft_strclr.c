#include "libft.h"

void	ft_strclr(char *s)
{
	ft_memset((void *)s, '\0', ft_strlen(s));
}

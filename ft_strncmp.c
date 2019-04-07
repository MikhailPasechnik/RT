#include "libft.h"
#include <stdio.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
    unsigned const char	*v1;
    unsigned const char	*v2;

    v1 = (unsigned const char *)s1;
    v2 = (unsigned const char *)s2;
    while (n--)
    {
        if (!*v1 || !*v2)
            return (*v1 - *v2);
        else if (*v1 != *v2)
            return (*v1 - *v2);
        v1++;
        v2++;
    }
    return (0);
}

#include "libft.h"

size_t  ft_strhash(const char *s, size_t size)
{
    size_t  hash;
    size_t  i;

    i = 0;
    hash = 0;
    while(s && s[i])
    {
        hash = (hash + s[i]) % size;
        i++;
    }
    return hash;
}

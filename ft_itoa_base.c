#include "libft.h"

#define TO_CHAR(n)(((n) > 9 ? (n) + 55 : (n) + '0'))

char    *ft_itoa_base(char *dest, int n, int base)
{
    size_t      len;
    int         tmp;

    if (base < 2 || base > 16)
        return (NULL);
    len = n > 0 ? 0 : 1;
    tmp = n;
    while (tmp && ++len)
        tmp /= base;
    if (!dest && (dest = ft_strnew(len)) == NULL)
        return (NULL);
    dest[0] = n == 0 ? '0' : '-';
    dest[len] = '\0';
    while (n && len--)
    {
        dest[len] = n > 0 ? TO_CHAR(n % base) : TO_CHAR(-(n % base));
        n /= base;
    }
    return (dest);
}

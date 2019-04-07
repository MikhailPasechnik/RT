#include "libft.h"

int     ft_tolower(int c)
{
    return (ft_isalpha(c) && c >= 'A' && c <= 'Z' ? c + 32 : c);
}

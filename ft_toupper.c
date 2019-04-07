#include "libft.h"

int     ft_toupper(int c)
{
    return (ft_isalpha(c) && c >= 'a' && c <= 'z' ? c - 32 : c);
}

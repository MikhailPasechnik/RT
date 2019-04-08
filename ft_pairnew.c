#include "libft.h"

t_pair  *ft_pairnew(void)
{
    t_pair  *new;
    if ((new = (t_pair *)ft_memalloc(sizeof(*new)))== NULL)
        return NULL;
    return (new);
}

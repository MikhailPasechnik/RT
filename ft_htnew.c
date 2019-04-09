#include "libft.h"

t_htable        *ft_htnew(size_t size,
                  int (*key_cmp)(void *, void *),
                  int (*key_del)(void *), int (*val_del)(void *))
{
    t_htable    *ht;
    if ((ht = ft_memalloc(sizeof(*ht))) == NULL)
        return (NULL);
    if ((ht->bins = ft_memalloc(sizeof(*ht->bins) * size)) == NULL)
    {
        ft_memdel((void **)&ht);
        return (NULL);
    }
    ht->size = size;
    ht->key_cmp = key_cmp;
    ht->key_del = key_del;
    ht->val_del = val_del;
    return (ht);
}

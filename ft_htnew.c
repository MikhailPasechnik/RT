#include "libft.h"

t_htable        *ft_htnew(size_t size,
						  int (*func_key_cmp)(void *, void *), int (*func_key_del)(void *),
						  int (*func_val_del)(void *), size_t (*func_key_hash)(void *, size_t))
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
    ht->func_key_cmp = func_key_cmp;
    ht->func_key_del = func_key_del;
    ht->func_val_del = func_val_del;
    ht->func_key_hash = func_key_hash;
    return (ht);
}

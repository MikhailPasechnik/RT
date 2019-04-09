#include "libft.h"

int             ft_htset(t_htable *ht, void *key, void *value)
{
    size_t      hash;
    t_htentry   *entry;

    hash = ft_strhash(key, ht->size);
    entry = ht->bins[hash];
    while (entry)
    {
        if (ft_strcmp(entry->key, key) == 0)
        {
            entry->value = value;
            return (1);
        }
        entry = entry->next;
    }
    if ((entry = ft_memalloc(sizeof(*entry))) == NULL)
        return (0);
    *entry = (t_htentry){key, value, ht->bins[hash]};
    ht->bins[hash] = entry;
    return (1);
}

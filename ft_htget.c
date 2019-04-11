#include "libft.h"

void            *ft_htget(t_htable *ht, void *key) {
    t_htentry   *entry;

    if (ht && key)
    {
        entry = ht->bins[ht->func_key_hash(key, ht->size)];
        while (entry)
        {
            if (ht->func_key_cmp(entry->key, key) == 0)
                return (entry->value);
            entry = entry->next;
        }
    }
    return NULL;
}

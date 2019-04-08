#include "libft.h"

t_htable        *ft_htnew(size_t size)
{
    t_htable    *new;
    if ((new = ft_memalloc(sizeof(*new))) == NULL)
        return (NULL);
    if ((new->bins = ft_memalloc(sizeof(*new->bins) * size)) == NULL)
    {
        ft_memdel((void **)&new);
        return (NULL);
    }
    new->size = size;
    return (new);
}

static int      ft_keycmp(const void *pair, const void *pair2)
{
    if (!pair || !pair2 || !((t_pair *)pair)->key ||!((t_pair *)pair2)->key)
        return (-1);
    return ft_strcmp(((t_pair *)pair)->key, ((t_pair *)pair2)->key);
}

int             ft_htset(t_htable *ht, const char *key, const void *value)
{
    size_t  hash;
    t_list  *bin;
    t_pair  *pair;

    hash = ft_strhash(key, ht->size);
    if ((bin = ft_lstfind(ht->bins[hash], &(t_pair){key, value}, ft_keycmp)) != NULL)
    {
        bin->content = (void *)value;
        return (0);
    }
    if ((pair = ft_pairnew()) == NULL)
        return (0);
    *pair = (t_pair){key, value};
    if ((bin = ft_lstnew(pair, sizeof(*pair))) == NULL)
    {
        ft_memdel((void **)&pair);
        return (0);
    }
    ht->bins[hash] = bin;
    return (1);
}

void            *ft_htget(t_htable *ht, const char *key) {
    t_list  *bin;

    if (ht && key)
    {
        bin = ft_lstfind(ht->bins[ft_strhash(key, ht->size)],
                &(t_pair) {key, NULL}, ft_keycmp);
        return (bin);
    }
    return NULL;
}

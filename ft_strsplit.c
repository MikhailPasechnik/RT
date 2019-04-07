
#include "libft.h"

char			*ft_skip_delimiter(char *str)
{
    while (*str != '\0' && (*str == '\t' || *str == ' ' || *str == '\n'))
        str++;
    return (str);
}

unsigned int	ft_count_till_delimiter(char *str)
{
    int count;

    count = 0;
    while (*str != '\0' && *str != '\t' && *str != ' ' && *str != '\n')
    {
        str++;
        count++;
    }
    return (count);
}

int				ft_word_count(char *str)
{
    int count;
    int skip;

    count = 0;
    while (*str != '\0')
    {
        str = ft_skip_delimiter(str);
        skip = ft_count_till_delimiter(str);
        count += (skip > 0);
        str += skip;
    }
    return (count);
}

char			**ft_split_whitespaces(char *str)
{
    int			size;
    char		**result;
    int			till_delimeter;
    int			len;
    int			sub_len;

    size = ft_word_count(str);
    if ((result = malloc(sizeof(*result) * size + 1)) == NULL)
        return (NULL);
    len = 0;
    while (len < size)
    {
        str = ft_skip_delimiter(str);
        till_delimeter = ft_count_till_delimiter(str);
        sub_len = 0;
        if ((result[len] = malloc(sizeof(*result) * till_delimeter + 1))
            == NULL)
            return (NULL);
        while (sub_len < till_delimeter)
            result[len][sub_len++] = *str++;
        result[len][sub_len] = '\0';
        len++;
    }
    result[len] = NULL;
    return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:07:08 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/06 16:09:45 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memmove(void *dest, const void *src, size_t n)
{
    char        *d;
    const char  *s;


    if (dest > src)
    {

        d = dest;
        s = src;
        while (n--)
            d[n] = s[n];
        return (dest);

    }
    return ft_memcpy(dest, src, n);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:16:46 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:16:48 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*new;

	if ((new = ft_memalloc(sizeof(*new) * (size + 1))) == NULL)
		return (NULL);
	return (ft_memset(new, '\0', size + 1));
}

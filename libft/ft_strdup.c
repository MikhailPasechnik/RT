/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 14:59:00 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:11:54 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char *dup;

	dup = ft_memalloc(sizeof(char) * (ft_strlen(s) + 1));
	if (dup == NULL)
		return (NULL);
	return (ft_strcpy(dup, s));
}

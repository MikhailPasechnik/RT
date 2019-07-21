/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strlcat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/05/08 20:43:07 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	char	*d;

	d = ft_strnew(4);
	ft_strcpy(d, "a");
	FT_CMP(ft_strlcat(d, "bc", 3), 3, "==");
	FT_CMP(ft_strlcat(d, "bc", 3), 4, "==");
	FT_CMP(ft_strlcat(d, "bcd", 3), 5, "==");
	ft_strdel(&d);
	char *d2 = "the cake is a lie !\0I'm hidden lol";
	char b2[0xF00] = "there is no stars in the sky";
	ft_strlcat(b2, d2, ft_strlen(d2) + ft_strlen(b2));
	FT_IS(b2, "there is no stars in the skythe cake is a lie ");
	return (0);
}

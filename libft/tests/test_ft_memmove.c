/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_memmove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 10:24:41 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	char	a[100];
	char	*d;

	ft_strcpy(a, "lorem ipsum dolor sit amet");
	d = a + 1;
	ft_memmove(d, a, 4);
	FT_IS(d, "lore ipsum dolor sit amet");
	ft_strcpy(a, "lorem ipsum dolor sit amet");
	d = a + 1;
	ft_memmove(a, d, 4);
	FT_IS(a, "oremm ipsum dolor sit amet");
	FT_OK(ft_memmove(NULL, NULL, 4) == NULL);
	return (0);
}

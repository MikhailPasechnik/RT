/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strreverse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 10:36:35 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	char *a;

	a = ft_strnew(5);
	ft_strcpy(a, "12345");
	ft_strreverse(&a);
	FT_IS(a, "54321");
	ft_strreverse(NULL);
	a[2] = '\0';
	ft_strreverse(&a);
	FT_IS(a, "45");
	a[0] = '\0';
	FT_IS(a, "");
	free(a);
	return (0);
}

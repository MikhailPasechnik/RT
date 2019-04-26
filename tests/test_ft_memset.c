/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_memset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 10:26:16 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	char s0[5];
	char s1[5];
	char s2[2];
	char s3[2];

	ft_strcpy(s0, "....");
	ft_strcpy(s1, "....");
	FT_IS(ft_memset(s0, 'z', 4), memset(s1, 'z', 4));
	ft_strcpy(s2, "1");
	ft_strcpy(s3, "1");
	FT_IS(ft_memset(s2, 'z', 1), memset(s3, 'z', 1));
	return (0);
}

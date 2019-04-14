/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_itoa_base_ext.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:10:13 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	char d[5] = "abcd";
	char c[1] = "!";
	char *p = NULL;
	IS(ft_itoa_base_ext(d, 128, 10, 1), "128");
	IS(ft_itoa_base_ext(d, 11, 10, 1), "11");
	IS(ft_itoa_base_ext(d, 1, 10, 1), "1");
	IS(ft_itoa_base_ext(d, 0, 10, 1), "0");
	IS(ft_itoa_base_ext(d, -1, 10, 1), "-1");
	IS(ft_itoa_base_ext(d, -12, 10, 1), "-12");

	IS(ft_itoa_base_ext(d, 1, 2, 1), "1");
	IS(ft_itoa_base_ext(d, 0, 2, 1), "0");

	IS(ft_itoa_base_ext(d, 4096, 16, 1), "1000");
	IS(ft_itoa_base_ext(d, 128, 16, 1), "80");
	IS(ft_itoa_base_ext(d, 10, 16, 1), "A");
	IS((p = ft_itoa_base(4096, 16)), "1000");
	OK(c[0] == '!');
	free(p);
	return (0);
}

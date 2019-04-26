/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_itoa_base_ext.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 10:17:37 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	char	d[5];

	FT_IS(ft_itoa_base_ext(d, 128, 10, 1), "128");
	FT_IS(ft_itoa_base_ext(d, 11, 10, 1), "11");
	FT_IS(ft_itoa_base_ext(d, 1, 10, 1), "1");
	FT_IS(ft_itoa_base_ext(d, 0, 10, 1), "0");
	FT_IS(ft_itoa_base_ext(d, -1, 10, 1), "-1");
	FT_IS(ft_itoa_base_ext(d, -12, 10, 1), "-12");
	FT_IS(ft_itoa_base_ext(d, 1, 2, 1), "1");
	FT_IS(ft_itoa_base_ext(d, 0, 2, 1), "0");
	FT_IS(ft_itoa_base_ext(d, 4096, 16, 1), "1000");
	FT_IS(ft_itoa_base_ext(d, 128, 16, 1), "80");
	FT_IS(ft_itoa_base_ext(d, 10, 16, 1), "A");
	return (0);
}

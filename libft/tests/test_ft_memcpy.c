/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_memcpy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 10:24:25 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	char	d0[5];
	char	d1[1];

	ft_strcpy(d1, "");
	ft_strcpy(d0, "....");
	ft_memcpy(d0, "____", 5);
	FT_IS_MEM(d0, "____", 5);
	ft_memcpy(d0, "____", 1);
	FT_IS_MEM(d1, "", 1);
	FT_OK(ft_memcpy(NULL, NULL, 3) == NULL);
	return (0);
}

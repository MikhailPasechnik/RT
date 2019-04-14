/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_count_till.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/13 13:10:13 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	cmp(int c)
{
	return (!ft_iswhitespace(c));
}

int			main(void)
{
	CMP(ft_count_till("\n\n\na", 1, 0, cmp) , 3, "==");
	CMP(ft_count_till("a\n\n\n", -1, 3, cmp) , 3, "==");
	CMP(ft_count_till("a", 1, 0, cmp) , 0, "==");
	CMP(ft_count_till("a", -1, 1, cmp) , 0, "==");
	CMP(ft_count_till("", 1, 0, cmp) , 0, "==");
	CMP(ft_count_till("", -1, 0, cmp) , 0, "==");
	return (0);
}

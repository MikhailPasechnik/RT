/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_iswhitespace.c                             :+:      :+:    :+:   */
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
	OK(ft_iswhitespace('\t'));
	OK(ft_iswhitespace(' '));
	OK(ft_iswhitespace('\n'));
	OK(!ft_iswhitespace('\0'));
	OK(!ft_iswhitespace('1'));
	OK(!ft_iswhitespace('a'));
	return (0);
}

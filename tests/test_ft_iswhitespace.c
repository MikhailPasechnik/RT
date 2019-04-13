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
	FT_TAP_OK(ft_iswhitespace('\t'));
	FT_TAP_OK(ft_iswhitespace(' '));
	FT_TAP_OK(ft_iswhitespace('\n'));
	FT_TAP_OK(!ft_iswhitespace('\0'));
	FT_TAP_OK(!ft_iswhitespace('1'));
	FT_TAP_OK(!ft_iswhitespace('a'));
	return (0);
}

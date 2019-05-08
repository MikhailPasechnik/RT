/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/05/08 20:38:49 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	FT_IS(ft_strjoin("ab", "cd"), "abcd");
	FT_IS(ft_strjoin("", ""), "");
	FT_IS(ft_strjoin("ab", ""), "ab");
	FT_OK(ft_strjoin(NULL, NULL) == NULL);
	return (0);
}

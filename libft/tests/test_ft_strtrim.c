/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strtrim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/26 10:33:51 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		main(void)
{
	char	*a;

	a = ft_strtrim(" a ");
	FT_IS(a, "a");
	ft_strdel(&a);
	a = ft_strtrim(" \n\ta \n\t");
	FT_IS(a, "a");
	ft_strdel(&a);
	a = ft_strtrim(" \n\ta b\n\t");
	FT_IS(a, "a b");
	ft_strdel(&a);
	a = ft_strtrim(" \n\ta \n\tb\n\t");
	FT_IS(a, "a \n\tb");
	ft_strdel(&a);
	a = ft_strtrim(" \n\t");
	FT_IS(a, "");
	ft_strdel(&a);
	a = ft_strtrim("");
	FT_IS(a, "");
	ft_strdel(&a);
	FT_OK(ft_strtrim(NULL) == NULL);
	return (0);
}

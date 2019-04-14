/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strtrim.c                                  :+:      :+:    :+:   */
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
	char	*a;

	a = ft_strtrim(" a ");
	IS(a, "a");
	ft_strdel(&a);
	a = ft_strtrim(" \n\ta \n\t");
	IS(a, "a");
	ft_strdel(&a);
	a = ft_strtrim(" \n\ta b\n\t");
	IS(a, "a b");
	ft_strdel(&a);
	a = ft_strtrim(" \n\ta \n\tb\n\t");
	IS(a, "a \n\tb");
	ft_strdel(&a);
	a = ft_strtrim(" \n\t");
	IS(a, "");
	ft_strdel(&a);
	a = ft_strtrim("");
	IS(a, "");
	ft_strdel(&a);
	OK(ft_strtrim(NULL) == NULL);
	return (0);
}

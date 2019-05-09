/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strsplit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 09:23:34 by bnesoi            #+#    #+#             */
/*   Updated: 2019/05/09 14:55:55 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	check(char **r)
{
	FT_IS(r[0], "lorem ");
	FT_IS(r[1], "psum dolor s");
	FT_IS(r[2], "t amet, consectetur ad");
	FT_IS(r[3], "p");
	FT_IS(r[4], "sc");
	FT_IS(r[5], "ng el");
	FT_IS(r[6], "t. Sed non r");
	FT_IS(r[7], "sus. Suspend");
	FT_IS(r[8], "sse lectus tortor, d");
	FT_IS(r[9], "gn");
	FT_IS(r[10], "ss");
	FT_IS(r[11], "m s");
	FT_IS(r[12], "t amet, ad");
	FT_IS(r[13], "p");
	FT_IS(r[14], "sc");
	FT_IS(r[15], "ng nec, ultr");
	FT_IS(r[16], "c");
	FT_IS(r[17], "es sed, dolor. Cras elementum ultr");
	FT_IS(r[18], "c");
	FT_IS(r[19], "es d");
	FT_IS(r[20], "am. Maecenas l");
	FT_IS(r[21], "gula massa, var");
	FT_IS(r[22], "us a, semper congue, eu");
	FT_IS(r[23], "smod non, m");
	FT_IS(r[24], ".");
}

int			main(void)
{
	char	**r;
	int		i;

	i = 10;
	while (i--)
	{
		r = ft_strsplit_any(
			"lorem ipsum dolor sit amet, consectetur adipiscing elit. "
			"Sed non risus. Suspendisse lectus tortor, dignissim sit "
			"amet, adipiscing nec, ultricies sed, dolor. Cras elementum"
			" ultricies diam. Maecenas ligula massa, varius a, semper "
			"congue, euismod non, mi.", "i");
		check(r);
		FT_OK(r[25] == NULL);
	}
	return (0);
}

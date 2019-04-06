/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:56:41 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/06 15:23:49 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

void	test_bzero(void)
{
	char s0[5] = "....";
	char s1[5] = ",,,,";
	char s2[1] = "";
	char s3[1] = "";

	ft_bzero(s0, 4);
	bzero(s1, 4);
	ft_bzero(s2, 4);
	bzero(s3, 4);
	int i = 5;
	while (i--)
	{
		assert(s0[i] == s1[i]);
	}
}

void	test_memset(void)
{
	char s0[5] = "....";
	char s1[5] = "....";
	char s2[1] = "";
	char s3[1] = "";

	assert(strcmp(ft_memset(s0, 'z', 4), memset(s1, 'z', 4)) == 0);
	assert(strcmp(ft_memset(s2, 'z', 0), memset(s3, 'z', 0)) == 0);
}

int		main(void)
{
	test_bzero();
	test_memset();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:56:41 by bnesoi            #+#    #+#             */
/*   Updated: 2019/04/06 15:55:31 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

void	test_memccpy(void)
{
	char d0[5] = "..!.";
	char s0[5] = "__!_";
	char d0c[5] = "..!.";
	char d1[4] = "123";
	char s1[4] = "321";
	char d1c[4] = "123";
	assert(strcmp(ft_memccpy(d0, s0, '!', 4), memccpy(d0c, s0, '!', 4)) == 0);
	assert(ft_memccpy(d1, s1, '!', 4) == NULL &&
		memccpy(d1c, s1, '!', 4) == NULL);
}

void	test_memcpy(void)
{
	char d0[5] = "....";
	char s0[5] = "____";
	char d0c[5] = "....";
	char d1[1] = "";
	char s1[1] = "";
	char d1c[1] = "";

	assert(strcmp(ft_memcpy(d0, s0, 4), memcpy(d0c, s0, 4)) == 0);
	assert(strcmp(ft_memcpy(d1, s1, 0), memcpy(d1c, s1, 0)) == 0);
}

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
	test_memccpy();
	test_memset();
	test_bzero();
	test_memset();
	return (0);
}

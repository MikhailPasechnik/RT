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
#include <assert.h>
#include <strings.h>

#if defined(FT_MEMSET) || defined(FT_ALL) || defined(FT_PART1)
void	test_memset(void)
{
	char s0[5] = "....";
	char s1[5] = "....";
	char s2[1] = "";
	char s3[1] = "";

	assert(strcmp(ft_memset(s0, 'z', 4), memset(s1, 'z', 4)) == 0);
	assert(strcmp(ft_memset(s2, 'z', 0), memset(s3, 'z', 0)) == 0);
}

#endif
#if defined(FT_BZERO) || defined(FT_ALL) || defined(FT_PART1)
void	test_bzero(void)
{
	char s0[5] = "....";
	char s1[5] = ",,,,";
	char s2[1] = "";
	char s3[1] = "";

	ft_bzero(s0, 4);
	memset(s1, 0, sizeof(s1));
	ft_bzero(s2, 4);
	memset(s3, 0, sizeof(s3));
	int i = 5;
	while (i--)
	{
		assert(s0[i] == s1[i]);
	}
}
#endif
#if defined(FT_MEMCPY) || defined(FT_ALL) || defined(FT_PART1)
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
#endif
#if defined(FT_MEMCCPY) || defined(FT_ALL) || defined(FT_PART1)
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
#endif
#if defined(FT_MEMMOVE) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_MEMCHR) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_MEMCMP) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRLEN) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRDUP) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRCPY) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRNCPY) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRCAT) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRNCAT) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRLCAT) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRCHR) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRRCHR) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRSTR) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRNSTR) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRCMP) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRNCMP) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_ATOI) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_ISALPHA) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_ISDIGIT) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_ISALNUM) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_ISASCII) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_ISPRINT) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_TOUPPER) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_TOLOWER) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_MEMALLOC) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_MEMDEL) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRNEW) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRDEL) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRCLR) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRITER) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRITERI) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRMAP) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRMAPI) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STREQU) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRNEQU) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRSUB) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRJOIN) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRTRIM) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRSPLIT) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_ITOA) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_PUTCHAR) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_PUTSTR) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_PUTENDL) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_PUTNBR) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_PUTCHAR_FD) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_PUTSTR_FD) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_PUTENDL_FD) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_PUTNBR_FD) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_LSTNEW) || defined(FT_ALL) || defined(FT_EXTRA)
#endif
#if defined(FT_LSTDELONE) || defined(FT_ALL) || defined(FT_EXTRA)
#endif
#if defined(FT_LSTDEL) || defined(FT_ALL) || defined(FT_EXTRA)
#endif
#if defined(FT_LSTADD) || defined(FT_ALL) || defined(FT_EXTRA)
#endif
#if defined(FT_LSTITER) || defined(FT_ALL) || defined(FT_EXTRA)
#endif
#if defined(FT_LSTMAP) || defined(FT_ALL) || defined(FT_EXTRA)
#endif
#if defined(FT_COUNT_TILL) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_ISWHITESPACE) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_LSTREVERSE) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_STACK_NEW) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_STACK_DEL) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_STACK_POP) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_STACK_PUSH) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_QUEUE_NEW) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_DEQUEUE) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_ENQUEUE) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_QUEUE_DEL) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif

int		main()
{
#if defined(FT_MEMSET) || defined(FT_ALL) || defined(FT_PART1)
	test_memset();
#endif
#if defined(FT_BZERO) || defined(FT_ALL) || defined(FT_PART1)
	test_bzero();
#endif
#if defined(FT_MEMCPY) || defined(FT_ALL) || defined(FT_PART1)
	test_memcpy();
#endif
#if defined(FT_MEMCCPY) || defined(FT_ALL) || defined(FT_PART1)
	test_memccpy();
#endif
#if defined(FT_MEMMOVE) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_MEMCHR) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_MEMCMP) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRLEN) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRDUP) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRCPY) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRNCPY) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRCAT) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRNCAT) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRLCAT) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRCHR) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRRCHR) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRSTR) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRNSTR) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRCMP) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_STRNCMP) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_ATOI) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_ISALPHA) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_ISDIGIT) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_ISALNUM) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_ISASCII) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_ISPRINT) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_TOUPPER) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_TOLOWER) || defined(FT_ALL) || defined(FT_PART1)
#endif
#if defined(FT_MEMALLOC) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_MEMDEL) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRNEW) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRDEL) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRCLR) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRITER) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRITERI) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRMAP) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRMAPI) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STREQU) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRNEQU) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRSUB) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRJOIN) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRTRIM) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_STRSPLIT) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_ITOA) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_PUTCHAR) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_PUTSTR) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_PUTENDL) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_PUTNBR) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_PUTCHAR_FD) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_PUTSTR_FD) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_PUTENDL_FD) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_PUTNBR_FD) || defined(FT_ALL) || defined(FT_PART2)
#endif
#if defined(FT_LSTNEW) || defined(FT_ALL) || defined(FT_EXTRA)
#endif
#if defined(FT_LSTDELONE) || defined(FT_ALL) || defined(FT_EXTRA)
#endif
#if defined(FT_LSTDEL) || defined(FT_ALL) || defined(FT_EXTRA)
#endif
#if defined(FT_LSTADD) || defined(FT_ALL) || defined(FT_EXTRA)
#endif
#if defined(FT_LSTITER) || defined(FT_ALL) || defined(FT_EXTRA)
#endif
#if defined(FT_LSTMAP) || defined(FT_ALL) || defined(FT_EXTRA)
#endif
#if defined(FT_COUNT_TILL) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_ISWHITESPACE) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_LSTREVERSE) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_STACK_NEW) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_STACK_DEL) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_STACK_POP) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_STACK_PUSH) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_QUEUE_NEW) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_DEQUEUE) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_ENQUEUE) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
#if defined(FT_QUEUE_DEL) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
	return (0);
}

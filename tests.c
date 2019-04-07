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

void	test_ft_memset(void)
{
#if defined(FT_MEMSET) || defined(FT_ALL) || defined(FT_PART1)
    char s0[5] = "....";
    char s1[5] = "....";
    char s2[2] = "1";
    char s3[2] = "1";

    assert(strcmp(ft_memset(s0, 'z', 4), memset(s1, 'z', 4)) == 0);
    assert(strcmp(ft_memset(s2, 'z', 1), memset(s3, 'z', 1)) == 0);
#endif
}
void	test_ft_bzero(void)
{
#if defined(FT_BZERO) || defined(FT_ALL) || defined(FT_PART1)
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
        assert(s0[i] == ' ');
    }
#endif
}
void	test_ft_memcpy(void)
{
#if defined(FT_MEMCPY) || defined(FT_ALL) || defined(FT_PART1)
    char d0[5] = "....";
    char s0[5] = "____";
    char d0c[5] = "....";
    char d1[1] = "";
    char s1[1] = "";
    char d1c[1] = "";

    assert(strcmp(ft_memcpy(d0, s0, 4), memcpy(d0c, s0, 4)) == 0);
    assert(strcmp(ft_memcpy(d1, s1, 0), memcpy(d1c, s1, 0)) == 0);
#endif
}
void	test_ft_memccpy(void)
{
#if defined(FT_MEMCCPY) || defined(FT_ALL) || defined(FT_PART1)
    char d0[5] = "..!.";
    char s0[5] = "__!_";
    char d0c[5] = "..!.";
    char d1[4] = "123";
    char s1[4] = "321";
    char d1c[4] = "123";
    assert(strcmp(ft_memccpy(d0, s0, '!', 4), memccpy(d0c, s0, '!', 4)) == 0);
    assert(ft_memccpy(d1, s1, '!', 4) == NULL && memccpy(d1c, s1, '!', 4) == NULL);
#endif
}
void	test_ft_memmove(void)
{
#if defined(FT_MEMMOVE) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_memchr(void)
{
#if defined(FT_MEMCHR) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_memcmp(void)
{
#if defined(FT_MEMCMP) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_strlen(void)
{
#if defined(FT_STRLEN) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_strdup(void)
{
#if defined(FT_STRDUP) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_strcpy(void)
{
#if defined(FT_STRCPY) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_strncpy(void)
{
#if defined(FT_STRNCPY) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_strcat(void)
{
#if defined(FT_STRCAT) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_strncat(void)
{
#if defined(FT_STRNCAT) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_strlcat(void)
{
#if defined(FT_STRLCAT) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_strchr(void)
{
#if defined(FT_STRCHR) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_strrchr(void)
{
#if defined(FT_STRRCHR) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_strstr(void)
{
#if defined(FT_STRSTR) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_strnstr(void)
{
#if defined(FT_STRNSTR) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_strcmp(void)
{
#if defined(FT_STRCMP) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_strncmp(void)
{
#if defined(FT_STRNCMP) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_atoi(void)
{
#if defined(FT_ATOI) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_isalpha(void)
{
#if defined(FT_ISALPHA) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_isdigit(void)
{
#if defined(FT_ISDIGIT) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_isalnum(void)
{
#if defined(FT_ISALNUM) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_isascii(void)
{
#if defined(FT_ISASCII) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_isprint(void)
{
#if defined(FT_ISPRINT) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_toupper(void)
{
#if defined(FT_TOUPPER) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_tolower(void)
{
#if defined(FT_TOLOWER) || defined(FT_ALL) || defined(FT_PART1)
#endif
}
void	test_ft_memalloc(void)
{
#if defined(FT_MEMALLOC) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_memdel(void)
{
#if defined(FT_MEMDEL) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_strnew(void)
{
#if defined(FT_STRNEW) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_strdel(void)
{
#if defined(FT_STRDEL) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_strclr(void)
{
#if defined(FT_STRCLR) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_striter(void)
{
#if defined(FT_STRITER) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_striteri(void)
{
#if defined(FT_STRITERI) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_strmap(void)
{
#if defined(FT_STRMAP) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_strmapi(void)
{
#if defined(FT_STRMAPI) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_strequ(void)
{
#if defined(FT_STREQU) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_strnequ(void)
{
#if defined(FT_STRNEQU) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_strsub(void)
{
#if defined(FT_STRSUB) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_strjoin(void)
{
#if defined(FT_STRJOIN) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_strtrim(void)
{
#if defined(FT_STRTRIM) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_strsplit(void)
{
#if defined(FT_STRSPLIT) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_itoa(void)
{
#if defined(FT_ITOA) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_putchar(void)
{
#if defined(FT_PUTCHAR) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_putstr(void)
{
#if defined(FT_PUTSTR) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_putendl(void)
{
#if defined(FT_PUTENDL) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_putnbr(void)
{
#if defined(FT_PUTNBR) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_putchar_fd(void)
{
#if defined(FT_PUTCHAR_FD) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_putstr_fd(void)
{
#if defined(FT_PUTSTR_FD) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_putendl_fd(void)
{
#if defined(FT_PUTENDL_FD) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_putnbr_fd(void)
{
#if defined(FT_PUTNBR_FD) || defined(FT_ALL) || defined(FT_PART2)
#endif
}
void	test_ft_lstnew(void)
{
#if defined(FT_LSTNEW) || defined(FT_ALL) || defined(FT_EXTRA)
#endif
}
void	test_ft_lstdelone(void)
{
#if defined(FT_LSTDELONE) || defined(FT_ALL) || defined(FT_EXTRA)
#endif
}
void	test_ft_lstdel(void)
{
#if defined(FT_LSTDEL) || defined(FT_ALL) || defined(FT_EXTRA)
#endif
}
void	test_ft_lstadd(void)
{
#if defined(FT_LSTADD) || defined(FT_ALL) || defined(FT_EXTRA)
#endif
}
void	test_ft_lstiter(void)
{
#if defined(FT_LSTITER) || defined(FT_ALL) || defined(FT_EXTRA)
#endif
}
void	test_ft_lstmap(void)
{
#if defined(FT_LSTMAP) || defined(FT_ALL) || defined(FT_EXTRA)
#endif
}
void	test_ft_count_till(void)
{
#if defined(FT_COUNT_TILL) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
}
void	test_ft_iswhitespace(void)
{
#if defined(FT_ISWHITESPACE) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
}
void	test_ft_lstreverse(void)
{
#if defined(FT_LSTREVERSE) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
}
void	test_ft_stack_new(void)
{
#if defined(FT_STACK_NEW) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
}
void	test_ft_stack_del(void)
{
#if defined(FT_STACK_DEL) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
}
void	test_ft_stack_pop(void)
{
#if defined(FT_STACK_POP) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
}
void	test_ft_stack_push(void)
{
#if defined(FT_STACK_PUSH) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
}
void	test_ft_queue_new(void)
{
#if defined(FT_QUEUE_NEW) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
}
void	test_ft_dequeue(void)
{
#if defined(FT_DEQUEUE) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
}
void	test_ft_enqueue(void)
{
#if defined(FT_ENQUEUE) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
}
void	test_ft_queue_del(void)
{
#if defined(FT_QUEUE_DEL) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
}
int		main()
{
    test_ft_memset();
    test_ft_bzero();
    test_ft_memcpy();
    test_ft_memccpy();
    test_ft_memmove();
    test_ft_memchr();
    test_ft_memcmp();
    test_ft_strlen();
    test_ft_strdup();
    test_ft_strcpy();
    test_ft_strncpy();
    test_ft_strcat();
    test_ft_strncat();
    test_ft_strlcat();
    test_ft_strchr();
    test_ft_strrchr();
    test_ft_strstr();
    test_ft_strnstr();
    test_ft_strcmp();
    test_ft_strncmp();
    test_ft_atoi();
    test_ft_isalpha();
    test_ft_isdigit();
    test_ft_isalnum();
    test_ft_isascii();
    test_ft_isprint();
    test_ft_toupper();
    test_ft_tolower();
    test_ft_memalloc();
    test_ft_memdel();
    test_ft_strnew();
    test_ft_strdel();
    test_ft_strclr();
    test_ft_striter();
    test_ft_striteri();
    test_ft_strmap();
    test_ft_strmapi();
    test_ft_strequ();
    test_ft_strnequ();
    test_ft_strsub();
    test_ft_strjoin();
    test_ft_strtrim();
    test_ft_strsplit();
    test_ft_itoa();
    test_ft_putchar();
    test_ft_putstr();
    test_ft_putendl();
    test_ft_putnbr();
    test_ft_putchar_fd();
    test_ft_putstr_fd();
    test_ft_putendl_fd();
    test_ft_putnbr_fd();
    test_ft_lstnew();
    test_ft_lstdelone();
    test_ft_lstdel();
    test_ft_lstadd();
    test_ft_lstiter();
    test_ft_lstmap();
    test_ft_count_till();
    test_ft_iswhitespace();
    test_ft_lstreverse();
    test_ft_stack_new();
    test_ft_stack_del();
    test_ft_stack_pop();
    test_ft_stack_push();
    test_ft_queue_new();
    test_ft_dequeue();
    test_ft_enqueue();
    test_ft_queue_del();
	return (0);
}

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

void	test_ft_memset(void)
{
#if defined(FT_MEMSET) || defined(FT_ALL) || defined(FT_PART1)
    char s0[5] = "....";
    char s1[5] = "....";
    is(ft_memset(s0, 'z', 4), memset(s1, 'z', 4));
    char s2[2] = "1";
    char s3[2] = "1";
    is(ft_memset(s2, 'z', 1), memset(s3, 'z', 1));
    // dies_ok({ft_memset("", 'z', -1);});
#endif
}
void	test_ft_bzero(void)
{
#if defined(FT_BZERO) || defined(FT_ALL) || defined(FT_PART1)
    char s0[5] = "....";
    ft_bzero(s0, 5);
	ismem(s0, "\0\0\0\0\0", 5, "complete bzero");
    // dies_ok({ft_bzero("", -1);});
#endif
}
void	test_ft_memcpy(void)
{
#if defined(FT_MEMCPY) || defined(FT_ALL) || defined(FT_PART1)
    char d0[5] = "....";
    ft_memcpy(d0, "____", 5);
	ismem(d0, "____", 5);
    char d1[1] = "";
    ft_memcpy(d0, "____", 1);
	ismem(d1, "", 1);
    // dies_ok({ft_memcpy("", "", -1);});
#endif
}
void	test_ft_memccpy(void)
{
#if defined(FT_MEMCCPY) || defined(FT_ALL) || defined(FT_PART1)
    char d0[5] = "..!.";
    ft_memccpy(d0, "__!_", '!', 5);
    is(d0, "__!.");
    ft_memccpy(d0, "__!_", '_', 5);
    is(d0, "__!.");
    ft_memccpy(d0, "\0__!", '!', 5);
	ismem(d0, "\0__!", 5);
    // dies_ok({ft_memccpy("", "", 'd', -1);});
#endif
}
void	test_ft_memmove(void)
{
#if defined(FT_MEMMOVE) || defined(FT_ALL) || defined(FT_PART1)
    char    a[] = "lorem ipsum dolor sit amet";
    char	*d;
    d = a + 1;
    ft_memmove(d, a, 4);
    is(d, "lore ipsum dolor sit amet");
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
void	test_ft_itoa_base(void)
{
#if defined(FT_ITOA_BASE) || defined(FT_ALL) || defined(FT_EXTRA)
    char d[5] = "abcd";
    char c[1] = "!";
    char *p = NULL;
    is(ft_itoa_base_ext(d, 128, 10, 1), "128");
    is(ft_itoa_base_ext(d, 11, 10, 1), "11");
    is(ft_itoa_base_ext(d, 1, 10, 1), "1");
    is(ft_itoa_base_ext(d, 0, 10, 1), "0");
    is(ft_itoa_base_ext(d, -1, 10, 1), "-1");
    is(ft_itoa_base_ext(d, -12, 10, 1), "-12");

    is(ft_itoa_base_ext(d, 1, 2, 1), "1");
    is(ft_itoa_base_ext(d, 0, 2, 1), "0");

    is(ft_itoa_base_ext(d, 4096, 16, 1), "1000");
    is(ft_itoa_base_ext(d, 128, 16, 1), "80");
    is(ft_itoa_base_ext(d, 10, 16, 1), "A");
    is((p = ft_itoa_base(4096, 16)), "1000");
    ok(c[0] == '!');
    free(p);
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
    ok(ft_iswhitespace('\t'));
    ok(ft_iswhitespace(' '));
    ok(ft_iswhitespace('\n'));
    ok(!ft_iswhitespace('\0'));
    ok(!ft_iswhitespace('1'));
    ok(!ft_iswhitespace('a'));
#endif
}
void	test_ft_lstreverse(void)
{
#if defined(FT_LSTREVERSE) || defined(FT_ALL) || defined(FT_EXTRA2)
    t_list *l;
    t_list c = {"c", 2, NULL};
    t_list b = {"b", 2, &c};
    t_list a = {"a", 2, &b};
    l = &a;
    ft_lstreverse(&l);
    is(l->content, "c");
    is(l->next->content, "b");
    is(l->next->next->content, "a");
    // lives_ok({ft_lstreverse(NULL);});
#endif
}
void	test_ft_stack_new(void)
{
#if defined(FT_STACK_NEW) || defined(FT_ALL) || defined(FT_EXTRA2)
    t_stack *s = ft_stack_new();
    ok(!s->top);
    free(s);
#endif
}
void    stack_del(void *c, size_t s)
{
    memset(c, '!', s);
    (void)c;
    (void)s;
}
void	test_ft_stack_del(void)
{
#if defined(FT_STACK_DEL) || defined(FT_ALL) || defined(FT_EXTRA2)
    t_stack *s = malloc(sizeof(t_stack));
    t_list  *l = malloc(sizeof(t_list));
    char c[] = ".....";
    *l = (t_list){c, 4, NULL};
    s->top = l;
    ft_stack_del(&s, stack_del);
    ok(s == NULL);
    is(c, "!!!!.");
#endif
}
void	test_ft_stack_pop(void)
{
#if defined(FT_STACK_POP) || defined(FT_ALL) || defined(FT_EXTRA2)
    t_list  l2 = {"2", 1, NULL};
    t_list  l1 = {"1", 1, &l2};
    t_stack s = {&l1};
    is(ft_stack_pop(&s)->content, "1");
    is(ft_stack_pop(&s)->content, "2");
    ok(!s.top);
#endif
}
void	test_ft_stack_push(void)
{
#if defined(FT_STACK_PUSH) || defined(FT_ALL) || defined(FT_EXTRA2)
    t_list  l4 = {"4", 1, NULL};
    t_list  l3 = {"3", 1, NULL};
    t_list  l2 = {"2", 1, NULL};
    t_list  l1 = {"1", 1, NULL};
    t_stack s = {NULL};
    ft_stack_push(&s, &l1);
    ft_stack_push(&s, &l2);
    ft_stack_push(&s, &l3);
    ft_stack_push(&s, &l4);
    is(s.top->content, "4");
    is(s.top->next->content, "3");
#endif
}
void	test_ft_queue_new(void)
{
#if defined(FT_QUEUE_NEW) || defined(FT_ALL) || defined(FT_EXTRA2)
    t_queue *q = ft_queue_new();
    ok(!q->front);
    ok(!q->rear);
    free(q);
#endif
}
void	test_ft_dequeue(void)
{
#if defined(FT_DEQUEUE) || defined(FT_ALL) || defined(FT_EXTRA2)
    t_list  l2 = {"2", 1, NULL};
    t_list  l1 = {"1", 1, &l2};
    t_queue q = {&l1, &l2};
    t_list  dq = *ft_dequeue(&q);
    is(dq.content, "1");
    is(q.rear->content, "2");
    is(q.front->content, "2");
    dq = *ft_dequeue(&q);
    is(dq.content, "2");
    ok(q.rear == NULL);
    ok(q.front == NULL);
#endif
}
void	test_ft_enqueue(void)
{
#if defined(FT_ENQUEUE) || defined(FT_ALL) || defined(FT_EXTRA2)
    t_list  l4 = {"4", 1, NULL};
    t_list  l3 = {"3", 1, NULL};
    t_list  l2 = {"2", 1, NULL};
    t_list  l1 = {"1", 1, NULL};
    t_queue q = {NULL, NULL};
    ft_enqueue(&q, &l1);
    ft_enqueue(&q, &l2);
    ft_enqueue(&q, &l3);
    ft_enqueue(&q, &l4);
    is(ft_dequeue(&q)->content, "1");
    is(ft_dequeue(&q)->content, "2");
    is(ft_dequeue(&q)->content, "3");
    is(ft_dequeue(&q)->content, "4");
    ok(q.front == NULL);
    ok(q.rear == NULL);
#endif
}
void	test_ft_queue_del(void)
{
#if defined(FT_QUEUE_DEL) || defined(FT_ALL) || defined(FT_EXTRA2)
    t_queue *q;
    q = malloc(sizeof(*q));
    t_list  *l;
	l = malloc(sizeof(*l));
    char c[] = ".....";
    *l = (t_list){c, 4, NULL};
    q->rear = l;
    q->front = l;
    ft_queue_del(&q, stack_del);
    ok(q == NULL);
    is(c, "!!!!.");
#endif
}
void	test_ft_print_bits_fd(void)
{
#if defined(FT_PRINT_BITS_FD) || defined(FT_ALL) || defined(FT_EXTRA)
	int n = 2147483647;
	ft_print_bits_fd(sizeof(n), &n, 1);
	ft_putchar('\n');
#endif
}
void	test_ft_htnew(void)
{
#if defined(FT_HTNEW) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
}
void	test_ft_htset(void)
{
#if defined(FT_HTSET) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
}
void	test_ft_htget(void)
{
#if defined(FT_HTGET) || defined(FT_ALL) || defined(FT_EXTRA2)
#endif
}
void	test_ft_htdel(void)
{
#if defined(FT_HTDEL) || defined(FT_ALL) || defined(FT_EXTRA2)
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
	test_ft_print_bits_fd();
    test_ft_itoa_base();
    test_ft_htnew();
    test_ft_htset();
    test_ft_htget();
    test_ft_htdel();
	return (0);
}

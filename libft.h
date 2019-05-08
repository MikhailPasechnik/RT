/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:17:05 by bnesoi            #+#    #+#             */
/*   Updated: 2019/05/08 20:28:20 by bnesoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *dest, const char *src, size_t n);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *nptr);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_iswhitespace(int c);
char			*ft_strlowcase(char *str);
char			*ft_strcapitalize(char *str);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			**ft_strsplit_any(char const *s, char *c);
char			**ft_strsplit_word(char const *s, char *w);
char			*ft_itoa(int n);
char			*ft_itoa_base(int n, int base);
char			*ft_itoa_base_ext(char *dest, int n, int base, int sign);
size_t			ft_count_till(const char *str, int dir, size_t start,
					int (*cmp)(int));
void			ft_strreverse(char **str);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_print_bits_fd(size_t size, void *ptr, int fd);
int				ft_power(int nb, int power);
size_t			ft_strhash(const char *s, size_t size);

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstreverse(t_list **alst);
t_list			*ft_lstfind(struct s_list *lst, const void *ref,
	int (*cmp)(const void *, const void *));

typedef struct	s_stack
{
	t_list		*top;
}				t_stack;
t_stack			*ft_stack_new(void);
void			ft_stack_del(t_stack **stack, void (*del)(void *, size_t));
t_list			*ft_stack_pop(t_stack *stack);
void			ft_stack_push(t_stack *stack, t_list *new);
typedef struct	s_queue {
	t_list		*front;
	t_list		*rear;
}				t_queue;
t_queue			*ft_queue_new(void);
t_list			*ft_dequeue(t_queue *queue);
void			ft_enqueue(t_queue *queue, t_list *item);
void			ft_queue_del(t_queue **queue, void (*del)(void *, size_t));

typedef struct	s_htentry
{
	void				*key;
	void				*value;
	struct s_htentry	*next;
}				t_htentry;
typedef struct	s_htable
{
	size_t				size;
	t_htentry			**bins;
	int					(*func_key_cmp)(void *, void *);
	size_t				(*func_key_hash)(void *, size_t);
	void				(*func_key_value_del)(void *, void *);
}				t_htable;
t_htable		*ft_htnew(size_t size,
	int (*func_key_cmp)(void *, void *),
	size_t (*func_key_hash)(void *, size_t),
	void (*func_key_value_del)(void *, void *));
int				ft_htset(t_htable *ht, void *key, void *value);
void			*ft_htget(t_htable *ht, void *key);
void			ft_htdel(t_htable **ht);

typedef struct	s_plc
{
	const char	*file;
	int			line;
}				t_plc;
void			ft_tap_ok(t_plc place, int a);
void			ft_tap_is(t_plc place, const char *a, const char *b);
void			ft_tap_ismem(t_plc place, const char *a, const char *b,
	size_t n);
void			ft_tap_cmp(t_plc place, int a, int b, char *cmp);

# define FT_IS(...)(ft_tap_is((t_plc){__FILE__, __LINE__}, __VA_ARGS__))
# define FT_OK(...)(ft_tap_ok((t_plc){__FILE__, __LINE__}, __VA_ARGS__))
# define FT_IS_MEM(...)	(ft_tap_ismem((t_plc){__FILE__, __LINE__}, __VA_ARGS__))
# define FT_CMP(...)(ft_tap_cmp((t_plc){__FILE__, __LINE__}, __VA_ARGS__))
# define FT_ISLOWER(c)(((c) >= 'a' && (c) <= 'z'))
# define FT_ISUPPER(c)(((c) >= 'A' && (c) <= 'Z'))

#endif

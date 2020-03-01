# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/11 15:11:22 by bnesoi            #+#    #+#              #
#    Updated: 2020/03/01 20:35:38 by bmahi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a
SONAME=libft.so
FUNS=\
	ft_lstnew         ft_queue_new    ft_strmapi      ft_strhash           \
	ft_lstreverse     ft_stack_del    ft_strncat                           \
	ft_atoi           ft_memalloc     ft_stack_new    ft_strncmp           \
	ft_bzero          ft_memccpy      ft_stack_pop    ft_strncpy           \
	ft_count_till     ft_memchr       ft_stack_push   ft_strnequ           \
	ft_dequeue        ft_memcmp       ft_strcat       ft_strnew            \
	ft_enqueue        ft_memcpy       ft_strchr       ft_strnstr           \
	ft_isalnum        ft_memdel       ft_strclr       ft_strrchr           \
	ft_isalpha        ft_memmove      ft_strcmp       ft_strsplit          \
	ft_isascii        ft_memset       ft_strcpy       ft_strstr            \
	ft_isdigit        ft_putchar      ft_strdel       ft_strsub            \
	ft_isprint        ft_putchar_fd   ft_strdup       ft_strtrim           \
	ft_iswhitespace   ft_putendl      ft_strequ       ft_tolower           \
	ft_itoa           ft_putendl_fd   ft_striter      ft_toupper           \
	ft_lstadd         ft_putnbr       ft_striteri     ft_power             \
	ft_lstdel         ft_putnbr_fd    ft_strjoin      ft_lstfind           \
	ft_lstdelone      ft_putstr       ft_strlcat      ft_htnew             \
	ft_lstiter        ft_putstr_fd    ft_strlen       ft_itoa_base         \
	ft_lstmap         ft_queue_del    ft_strmap       ft_print_bits_fd     \
	ft_htdel          ft_htget        ft_htset        ft_itoa_base_ext     \
	ft_strlowcase	  ft_tap_is		  ft_tap_ok		  ft_tap_ismem         \
	ft_strcapitalize  ft_strreverse   ft_strsplit_any ft_strsplit_word	   \
	ft_tap_cmp        get_next_line

SRCS=$(addsuffix .c,$(FUNS))
OBJECT_FILES=$(addsuffix .o,$(FUNS))
GCC_FLAGS=-Wall -Wextra -Werror

all : $(NAME)

$(NAME) : ${OBJECT_FILES}
	@ar rc $(NAME) $(OBJECT_FILES)
	@ranlib $(NAME)

so : ${SRCS}
	@gcc $(GCC_FLAGS) ${SRCS} -fPIC -shared -o $(SONAME)

%.o: %.c libft.h
	@gcc $(GCC_FLAGS) -o $@ -c $<

clean :
	@/bin/rm -f $(OBJECT_FILES)

fclean : clean
	@/bin/rm -f $(NAME) $(addprefix tests/test_,$(FUNS))

re : fclean all

test-all:
	@for s in $(FUNS) ; do \
		if [ -f tests/test_$$s.c ]; then \
			$(MAKE) test fun=$$s --no-print-directory;\
        fi; \
	done

test: all
	@gcc  $(GCC_FLAGS) -L. tests/test_$(fun).c -lft -o tests/test_$(fun);
	$(info ************ $(fun))
	@tests/test_$(fun)

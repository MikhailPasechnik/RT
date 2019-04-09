# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bnesoi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/11 15:11:22 by bnesoi            #+#    #+#              #
#    Updated: 2019/03/12 18:58:05 by bnesoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a
SRCS=\
    ft_lstnew.c        ft_queue_new.c   ft_strmapi.c     ft_strhash.c          \
    ft_lstreverse.c    ft_stack_del.c   ft_strncat.c                           \
    ft_atoi.c          ft_memalloc.c    ft_stack_new.c   ft_strncmp.c          \
    ft_bzero.c         ft_memccpy.c     ft_stack_pop.c   ft_strncpy.c          \
    ft_count_till.c    ft_memchr.c      ft_stack_push.c  ft_strnequ.c          \
    ft_dequeue.c       ft_memcmp.c      ft_strcat.c      ft_strnew.c           \
    ft_enqueue.c       ft_memcpy.c      ft_strchr.c      ft_strnstr.c          \
    ft_isalnum.c       ft_memdel.c      ft_strclr.c      ft_strrchr.c          \
    ft_isalpha.c       ft_memmove.c     ft_strcmp.c      ft_strsplit.c         \
    ft_isascii.c       ft_memset.c      ft_strcpy.c      ft_strstr.c           \
    ft_isdigit.c       ft_putchar.c     ft_strdel.c      ft_strsub.c           \
    ft_isprint.c       ft_putchar_fd.c  ft_strdup.c      ft_strtrim.c          \
    ft_iswhitespace.c  ft_putendl.c     ft_strequ.c      ft_tolower.c          \
    ft_itoa.c          ft_putendl_fd.c  ft_striter.c     ft_toupper.c          \
    ft_lstadd.c        ft_putnbr.c      ft_striteri.c    ft_power.c            \
    ft_lstdel.c        ft_putnbr_fd.c   ft_strjoin.c     ft_lstfind.c          \
    ft_lstdelone.c     ft_putstr.c      ft_strlcat.c     ft_htnew.c            \
    ft_lstiter.c       ft_putstr_fd.c   ft_strlen.c                            \
    ft_lstmap.c        ft_queue_del.c   ft_strmap.c                            \
    ft_htdel.c         ft_htget.c       ft_htset.c                             \
    ft_tap_ok.c        ft_tap_is.c      ft_tap_ismem.c
OBJECT_FILES=\
    ft_lstnew.o        ft_queue_new.o   ft_strmapi.o     ft_strhash.o          \
    ft_lstreverse.o    ft_stack_del.o   ft_strncat.o                           \
    ft_atoi.o          ft_memalloc.o    ft_stack_new.o   ft_strncmp.o          \
    ft_bzero.o         ft_memccpy.o     ft_stack_pop.o   ft_strncpy.o          \
    ft_count_till.o    ft_memchr.o      ft_stack_push.o  ft_strnequ.o          \
    ft_dequeue.o       ft_memcmp.o      ft_strcat.o      ft_strnew.o           \
    ft_enqueue.o       ft_memcpy.o      ft_strchr.o      ft_strnstr.o          \
    ft_isalnum.o       ft_memdel.o      ft_strclr.o      ft_strrchr.o          \
    ft_isalpha.o       ft_memmove.o     ft_strcmp.o      ft_strsplit.o         \
    ft_isascii.o       ft_memset.o      ft_strcpy.o      ft_strstr.o           \
    ft_isdigit.o       ft_putchar.o     ft_strdel.o      ft_strsub.o           \
    ft_isprint.o       ft_putchar_fd.o  ft_strdup.o      ft_strtrim.o          \
    ft_iswhitespace.o  ft_putendl.o     ft_strequ.o      ft_tolower.o          \
    ft_itoa.o          ft_putendl_fd.o  ft_striter.o     ft_toupper.o          \
    ft_lstadd.o        ft_putnbr.o      ft_striteri.o    ft_power.o            \
    ft_lstdel.o        ft_putnbr_fd.o   ft_strjoin.o     ft_lstfind.o          \
    ft_lstdelone.o     ft_putstr.o      ft_strlcat.o     ft_htnew.o            \
    ft_lstiter.o       ft_putstr_fd.o   ft_strlen.o                            \
    ft_lstmap.o        ft_queue_del.o   ft_strmap.o                            \
    ft_htdel.o         ft_htget.o       ft_htset.o                             \
    ft_tap_ok.o        ft_tap_is.o      ft_tap_ismem.o
GCC_FLAGS=-Wall -Wextra -Werror
all : $(NAME)

$(NAME) :
	@gcc $(GCC_FLAGS) -c $(SRCS)
	@ar rc $(NAME) $(OBJECT_FILES)
	@ranlib $(NAME)

clean :
	@/bin/rm -f $(OBJECT_FILES) tests

fclean : clean
	@/bin/rm -f $(NAME)

re : fclean all

test : all
	@gcc  $(GCC_FLAGS) -L. tests.c -lft -D$(name) -o tests
	$(info ************ Test $(name) .. **********)
	./tests

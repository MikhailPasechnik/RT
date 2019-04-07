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
SRCS=ft_*.c
OBJECT_FILES=ft_*.o
HEADERS_FOLDER=./includes

all : $(NAME)

$(NAME) :
	@gcc -Wall -Wextra -Werror -I$(HEADERS_FOLDER) -c $(SRCS)
	@ar rc $(NAME) $(OBJECT_FILES)
	@ranlib $(NAME)

clean :
	@/bin/rm -f $(OBJECT_FILES)

fclean : clean
	@/bin/rm -f $(NAME)

re : fclean all

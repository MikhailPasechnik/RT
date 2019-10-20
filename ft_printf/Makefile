# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caellis <caellis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/11 15:11:22 by bnesoi            #+#    #+#              #
#    Updated: 2019/08/23 13:27:56 by caellis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a

INC_DIR=./include
OBJ_DIR=./obj
SRC_DIR=./src

SRC_FILES=\
	ft_printf.c			\
	pf_parse.c			\
	pf_put.c			\
	pf_put_char.c		\
	pf_put_int.c	    \
	pf_put_float.c		\
	pf_put_empty.c		\
	pf_put_string.c		\
	pf_put_prefix.c		\
	pf_put_ptr.c		\
	pf_atoi.c		    \
	pf_long_math.c	    \
	pf_strreverse.c		\
	pf_util.c			\
	pf_util_2.c
HDR_FILES=\
	ft_printf.h

HDR=$(addprefix $(INC_DIR)/, $(HDR_FILES))
OBJ=$(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
SRC=$(addprefix $(SRC_DIR)/, $(SRC_FILES))

CC=gcc
CC_FLAGS= -Wall -Wextra -Werror

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	$(CC) $(CC_FLAGS) -I $(INC_DIR) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean :
	@/bin/rm -rf $(OBJ_DIR)

fclean : clean
	@/bin/rm -f $(NAME)

re : fclean all

.PHONY: -

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bnesoi <bnesoi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/11 15:11:22 by bnesoi            #+#    #+#              #
#    Updated: 2019/07/10 13:57:12 by bnesoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fractol

OS			:=	$(shell uname -s)
SRC			:=	create_img.c start.c hooks.c main.c finish.c
HEADERS		=	fractol.h keys.h
LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft
INC_DIR		=	./includes
OBJ_DIR		=	./obj
SRC_DIR		=	./src

ifeq ($(OS),Linux)
    MINILIBX_DIR=./minilibx
    MINILIBX_LINK=-L$(MINILIBX_DIR) -lmlx -lXext -lX11
else
    MINILIBX_DIR=./minilibx_macos
    MINILIBX_LINK=-L$(MINILIBX_DIR) -lmlx -framework OpenGL -framework AppKit
endif
MINILIBX=$(MINILIBX_DIR)/libmix.a

CC=gcc
CC_FLAGS=-Wall -Wextra -Werror

OBJ=$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
HEADERS_FILES=$(addprefix $(INC_DIR)/, $(HEADERS))
LIBS=-L$(LIBFT_DIR) -lft $(MINILIBX_LINK) -lm
INCLUDES=-I $(LIBFT_DIR) -I $(MINILIBX_DIR) -I $(INC_DIR)
TEST_NAMES=test_mat3 test_mat_inverse
TEST_SRC:=$(shell find src/ -maxdepth 1 -type f \( -regex ".*\.c" ! -name "main.c" \))

all: $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c $(HEADERS_FILES)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(LIBFT): FAKE
	@$(MAKE) -C $(LIBFT_DIR)/ --no-print-directory

$(MINILIBX): FAKE
	@$(MAKE) -C $(MINILIBX_DIR)/ --no-print-directory

$(NAME): $(LIBFT) $(MINILIBX) $(OBJ)
	@$(CC)  $(CC_FLAGS) -o $(NAME) $(OBJ) $(INCLUDES) $(LIBS);

clean :
	@/bin/rm -rf $(OBJ_DIR)
	@make clean -C $(info $(OS))$(LIBFT_DIR) --no-print-directory
	@make clean -C $(MINILIBX_DIR) --no-print-directory

fclean : clean
	@/bin/rm -f $(NAME) $(addprefix tests/test_,$(FILE_NAMES))
	@make fclean -C $(LIBFT_DIR) --no-print-directory
	@/bin/rm -f ${MINILIBX}
	@/bin/rm -f $(addprefix tests/,$(TEST_NAMES))

re : fclean all

test-all:
	@for s in $(TEST_NAMES) ; do \
		$(MAKE) test name=$$s --no-print-directory;\
	done

test: $(LIBFT) $(MINILIBX)
	@gcc  $(CC_FLAGS) $(INCLUDES) $(TEST_SRC) tests/$(name).c $(LIBS) -o tests/$(name);
	$(info ************ $(name) *************)
	@tests/$(name)

.PHONY: FAKE

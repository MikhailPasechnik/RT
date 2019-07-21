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

OS			=	$(shell uname -s)
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

SRC_FILES	=			\
	hooks.c 			\
	main.c 				\
	finish.c 			\
	ocl/ocl_error.c  	\
	ocl/ocl_init.c  	\
	ocl/ocl_program.c  	\
	ocl/ocl_utils.c

HDR_FILES	=			\
	fractol.h 			\
	keys.h 				\
	ocl.h


DIR_SRC		=	./src
DIR_INC		=	./include
DIR_OBJ		=	./obj

LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft

SDL_DIR		=	./SDL
SDL_DIST	=	$(PWD)/SDL/dist
SDL_LINK	=	`$(SDL_DIST)/bin/sdl2-config --cflags --libs`


SRC			=	$(addprefix $(DIR_SRC)/, $(SRC_FILES))
HDR			=	$(addprefix $(DIR_INC)/, $(HDR_FILES))
OBJ			=	$(addprefix $(DIR_OBJ)/, $(SRC_FILES:.c=.o))

INCLUDES	=	-I $(LIBFT_DIR) -I $(DIR_INC) -I $(SDL_DIR)/dist/include
LIBS		=	./libft/libft.a -lOpenCL -lm
all: $(NAME)

$(DIR_OBJ):
	@mkdir $(DIR_OBJ)
	@mkdir $(DIR_OBJ)/ocl

$(NAME): $(SDL_DIST)  $(DIR_OBJ) $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(DIR_OBJ)/%.o:$(DIR_SRC)/%.c $(SRC)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT): FAKE
	@$(MAKE) -C $(LIBFT_DIR)/ --no-print-directory

$(SDL_DIST):
	$(info ************ Compiling SDL *************)
	$(info --prefix=$(SDL_DIST))
	mkdir -p $(SDL_DIR)/tmp
	cd $(SDL_DIR)/tmp; ../configure --prefix=$(SDL_DIST)
	$(MAKE) -C $(SDL_DIR)/tmp
	$(MAKE) -C $(SDL_DIR)/tmp install > /dev/null

clean :
	@/bin/rm -rf $(DIR_OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean : clean
	/bin/rm -rf $(SDL_DIST) $(SDL_DIR)/tmp
	@/bin/rm -f $(NAME) $(addprefix tests/test_,$(FILE_NAMES))
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@/bin/rm -f $(addprefix tests/,$(TEST_NAMES))

re : fclean all

.PHONY: FAKE

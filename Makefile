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

NAME=RTv1

OS			=	$(shell uname -s)
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

SRC_FILES	=			\
	main.c 				\
	ocl/ocl_error.c  	\
	ocl/ocl_init.c  	\
	ocl/ocl_program.c  	\
	ocl/ocl_utils.c		\
	math3d/mat4.c  		\
	math3d/mat4_op.c  	\
	math3d/mat4_rts.c  	\
	math3d/mat4_transform.c  \
	math3d/mat4_utils.c \
	math3d/vec3.c  		\
	math3d/vec3_op.c


HDR_FILES	=			\
	rt.h 			\
	keys.h 				\
	ocl.h				\
	math3d.h


DIR_SRC		=	./src
DIR_INC		=	./include
DIR_OBJ		=	./obj

LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft

SDL_DIR		=	./SDL
SDL_DIST	=	$(PWD)/SDL/dist
SDL_INCLUDE =	$(SDL_DIR)/dist/include/SDL2
SDL_LINK	=	`$(SDL_DIST)/bin/sdl2-config --cflags --libs`


SRC			=	$(addprefix $(DIR_SRC)/, $(SRC_FILES))
HDR			=	$(addprefix $(DIR_INC)/, $(HDR_FILES))
OBJ			=	$(addprefix $(DIR_OBJ)/, $(SRC_FILES:.c=.o))

INCLUDES	=	-I $(LIBFT_DIR) -I $(DIR_INC) -I $(SDL_INCLUDE)
LIBS		:=	./libft/libft.a -lm

ifeq ($(OS),Linux)
	LIBS	:= $(LIBS) -lOpenCL
else
	LIBS	:= $(LIBS) -framework OpenCL
endif

all: $(NAME)

$(DIR_OBJ):
	@mkdir $(DIR_OBJ)
	@mkdir $(DIR_OBJ)/ocl
	@mkdir $(DIR_OBJ)/math3d

$(NAME): $(SDL_DIST)  $(DIR_OBJ) $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME) $(SDL_LINK)

$(DIR_OBJ)/%.o:$(DIR_SRC)/%.c $(HDR)
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
	$(info SDL_LINK: $(SDL_LINK))

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

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmahi <bmahi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/11 15:11:22 by bnesoi            #+#    #+#              #
#    Updated: 2020/03/17 12:37:37 by bmahi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=RTv1

OS			=	$(shell uname -s)
CC			=	gcc
CFLAGS		=	-Wall -Wextra  -Werror

SRC_FILES	=			\
	app.c				\
	app_utils.c			\
	events.c			\
	file_io.c			\
	main.c				\
	renderer.c			\
	buffer.c			\
	texture_buffer.c    \
	navigation.c		\
	parser.c			\
	parse_types.c		\
	array_attack.c		\
	is_valid.c			\
	read_scene.c		\
	update.c			\
	sync.c				\
	utils.c				\
	ocl/ocl_error.c  	\
	ocl/ocl_init.c  	\
	ocl/ocl_program.c  	\
	ocl/ocl_utils.c		\
	math3d/mat4.c  		\
	math3d/mat4_op.c  	\
	math3d/mat4_inv.c  	\
	math3d/mat4_rts.c  	\
	math3d/mat4_transform.c  \
	math3d/mat4_utils.c \
	math3d/vec3.c  		\
	math3d/vec3_op.c


HDR_FILES	=			\
	rt.h 			    \
	keys.h 				\
	obj.h 			    \
	file_io.h    	    \
	ocl.h				\
	math3d.h


DIR_SRC		=	./src
DIR_INC		=	./include
DIR_OBJ		=	./obj

LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft
PRINTF		= 	./ft_printf/libftprintf.a
PRINTF_DIR	= 	./ft_printf

SDL_DIR		=	./SDL
SDL_DIST	=	$(PWD)/SDL/dist
SDL_INCLUDE =	$(SDL_DIR)/dist/include/SDL2
SDL_LINK	=	`$(SDL_DIST)/bin/sdl2-config --cflags --libs`


SRC			=	$(addprefix $(DIR_SRC)/, $(SRC_FILES))
HDR			=	$(addprefix $(DIR_INC)/, $(HDR_FILES))
OBJ			=	$(addprefix $(DIR_OBJ)/, $(SRC_FILES:.c=.o))
OBJ_NO_MAIN =   $(shell echo $(OBJ)| sed 's/\.\/obj\/main.o//g')
INCLUDES	=	-I$(LIBFT_DIR) -I$(DIR_INC) -I$(SDL_INCLUDE) -I$(PRINTF_DIR)/include
LIBS		:=	$(LIBFT) $(PRINTF) -lm

ifeq ($(OS),Linux)
	LIBS	:= $(LIBS) -lOpenCL
else
	LIBS	:= $(LIBS) -framework OpenCL
endif

all: $(NAME)

$(DIR_OBJ):
	echo DIR_OBJ: "$(DIR_OBJ)"
	mkdir $(DIR_OBJ)
	mkdir $(DIR_OBJ)/ocl
	mkdir $(DIR_OBJ)/math3d

$(NAME): $(SDL_DIST)  $(DIR_OBJ) $(OBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME) $(SDL_LINK)

# FRO TEST's
test1: $(SDL_DIST)  $(DIR_OBJ) $(OBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -c $(INCLUDES) tests/cl_sandbox.c -o tests/cl_sandbox.o
	$(CC) $(CFLAGS)  $(OBJ_NO_MAIN) tests/cl_sandbox.o $(LIBS)  -o cl_sandbox1 $(SDL_LINK)

test2: $(SDL_DIST)  $(DIR_OBJ) $(OBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -c $(INCLUDES) tests1/cl_sandbox.c -o tests1/cl_sandbox.o
	$(CC) $(CFLAGS)  $(OBJ_NO_MAIN) tests1/cl_sandbox.o $(LIBS)  -o cl_sandbox2 $(SDL_LINK)

$(DIR_OBJ)/%.o:$(DIR_SRC)/%.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT): FAKE
	$(MAKE) -C $(LIBFT_DIR)/ --no-print-directory

$(PRINTF): FAKE
	$(MAKE) -C $(PRINTF_DIR)/ --no-print-directory

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
	@$(MAKE) -C $(PRINTF_DIR) clean --no-print-directory

fclean : clean
	/bin/rm -rf $(SDL_DIST) $(SDL_DIR)/tmp
	@/bin/rm -f $(NAME) $(addprefix tests/test_,$(FILE_NAMES))
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@$(MAKE) -C $(PRINTF_DIR) fclean --no-print-directory
	@/bin/rm -f $(addprefix tests/,$(TEST_NAMES))

re : fclean all

.PHONY: FAKE

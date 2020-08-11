# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cvernius <cvernius@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/11 15:11:22 by bnesoi            #+#    #+#              #
#    Updated: 2020/08/11 18:29:45 by cvernius         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

OS			=	$(shell uname -s)
CC			=	gcc
CFLAGS		=	-D HOST_DEVICE -Wall -Wextra  -Werror 

SRC_FILES	=			\
	app.c				\
	options.c			\
	app_set_kernel_buf.c	\
	app_utils.c			\
	app_cleanup.c		\
	events.c			\
	events_selection.c	\
	file_io.c			\
	main.c				\
	renderer.c			\
	buffer.c			\
	texture_buffer.c    \
	navigation.c		\
	parser.c			\
	parse_types.c		\
	parse_textures.c	\
	array_attack.c		\
	is_valid.c			\
	read_scene.c		\
	printing.c			\
	update.c			\
	sync.c				\
	utils.c				\
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
	gui/gui_color_pick.c  	\
	gui/gui_setup.c  		\
	gui/gui_single_pick.c  	\
	gui/gui_scene_loop.c  	\
	gui/gui_selection_loop.c  	\
	gui/gui_light_loop.c  	\
	gui/gui_vec_pick.c  	\
	math3d/vec3_op.c


HDR_FILES	=			\
	rt.h 			    \
	keys.h 				\
	obj.h 			    \
	file_io.h    	    \
	ocl.h				\
	gui.h				\
	math3d.h


DIR_SRC		=	./src
DIR_INC		=	./include
DIR_OBJ		=	./obj

LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft
PRINTF		= 	./ft_printf/libftprintf.a
PRINTF_DIR	= 	./ft_printf


SRC			=	$(addprefix $(DIR_SRC)/, $(SRC_FILES))
HDR			=	$(addprefix $(DIR_INC)/, $(HDR_FILES))
OBJ			=	$(addprefix $(DIR_OBJ)/, $(SRC_FILES:.c=.o))
OBJ_NO_MAIN =   $(shell echo $(OBJ)| sed 's/\.\/obj\/main.o//g')
INCLUDES	=	-I$(LIBFT_DIR) -I$(DIR_INC) -I$(PRINTF_DIR)/include -I./nuklear -I./stb_image
LIBS		:=	$(LIBFT) $(PRINTF) -lm

ifeq ($(OS),Linux)
	LIBS	:= $(LIBS) -lOpenCL -lSDL2 -lGL -lGLEW
else
	LIBS	:= $(LIBS) -framework OpenCL -L ~/.brew/lib -lSDL2 -framework OpenGL -lm -lGLEW
	INCLUDES += -I ~/.brew/include
endif

all: $(NAME)

$(DIR_OBJ):
	@./libs_install.sh
	echo DIR_OBJ: "$(DIR_OBJ)"
	mkdir $(DIR_OBJ)
	mkdir $(DIR_OBJ)/ocl
	mkdir $(DIR_OBJ)/math3d
	mkdir $(DIR_OBJ)/gui

$(NAME): $(DIR_OBJ) $(OBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(DIR_OBJ)/%.o:$(DIR_SRC)/%.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT): FAKE
	$(MAKE) -C $(LIBFT_DIR)/ --no-print-directory

$(PRINTF): FAKE
	$(MAKE) -C $(PRINTF_DIR)/ --no-print-directory

clean :
	@/bin/rm -rf $(DIR_OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(PRINTF_DIR) clean --no-print-directory

fclean : clean
	@/bin/rm -f $(NAME) $(addprefix tests/test_,$(FILE_NAMES))
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@$(MAKE) -C $(PRINTF_DIR) fclean --no-print-directory
	@/bin/rm -f $(addprefix tests/,$(TEST_NAMES))

re : fclean all

.PHONY: FAKE

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/13 14:56:19 by julnolle          #+#    #+#              #
#    Updated: 2020/06/25 11:25:55 by julnolle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include color.mk

NAME	= miniRT

# ---------------- CC ---------------- #

CC	= clang

ifeq ($(err), no)
	CFLAGS += -Wall
	CFLAGS += -Wextra
else
	CFLAGS += -Wall
	CFLAGS += -Wextra
	CFLAGS += -Werror
endif

ifeq ($(debug), 0)
	CFLAGS += -g3
else ifeq ($(debug), 1)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
else ifeq ($(debug), 2)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
	CFLAGS += -ansi
	CFLAGS += -pedantic
else ifeq ($(debug), 3)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
	CFLAGS += -ansi
	CFLAGS += -pedantic
	CFLAGS += -Wpadded
else ifeq ($(debug), 4)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
	CFLAGS += -ansi
	CFLAGS += -pedantic
	CFLAGS += -Wpadded
	CFLAGS += -Weverything
endif

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	MLX_DIR 	= ./minilibx-linux/
	MLX			= -L $(MLX_DIR) -lmlx -lX11 -lXext -lm
	ENV			= -D LINUX
else
	MLX_DIR 	= ./minilibx_opengl_20191021/
	MLX			= -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	ENV			=
endif

# ---------------- SRC --------------- #

# Debug Sources
# SRCS += debug.c

# Main Sources
SRCS += main.c

# Parsing Sources
SRCS += parser.c
SRCS += parsing_env.c
SRCS += parsing_env2.c
SRCS += parsing_obj.c
SRCS += parsing_obj2.c
SRCS += parsing_tests.c
SRCS += parsing_utils.c
SRCS += parsing_utils2.c
SRCS += parsing_utils3.c
SRCS += parsing_free.c

# Raytracing Sources
SRCS += cam_handler.c
SRCS += event_handler.c
SRCS += minirt_utils.c 
SRCS += minirt_utils2.c 
SRCS += vec_func.c
SRCS += vec_func2.c
SRCS += vec_func3.c
SRCS += vec_rotation.c
SRCS += raytracing.c
SRCS += color_set.c
SRCS += color_operations.c
SRCS += inter_sphere.c
SRCS += inter_plane.c
SRCS += inter_triangle.c
SRCS += inter_square.c
SRCS += inter_cylinder.c

# Bmp handler Sources
SRCS += bmp_create.c

# Gnl Sources
SRCS += get_next_line.c

vpath %.c srcs/
vpath %.c srcs/parsing/
vpath %.c srcs/raytracing/
vpath %.c srcs/math_vec_color/
vpath %.c srcs/gnl/
vpath %.c srcs/bmp_handler/

# ---------------- INC --------------- #

INCLUDES 	=	./includes/
HEAD 		= $(INCLUDES)minirt.h
ALL_INC		=  -I$(INCLUDES) -I$(LIBFT_DIR) -I$(MLX_DIR)

# ---------------- OBJ --------------- #

DIR_OBJS	= ./objs/
OBJS		= $(patsubst %.c, $(DIR_OBJS)%.o, $(SRCS))
#OBJS_BONUS	= $(BONUS:.c=.o)

# ---------------- LIB --------------- #

LIBFT_DIR 	= ./libft/
LIBFT 		= $(LIBFT_DIR)libft.a
LIB_LINK	= $(MLX) -L$(LIBFT_DIR) -lft

# --------- Compilation Rules -------- #

all: $(NAME)

fast:
	$(MAKE) re -j8

$(NAME):	$(LIBFT) compmlx $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(ALL_INC) $(LIB_LINK) -o $@
			@echo "$(_BOLD)$(_YELLOW)==> $@ linked$(_END)"

$(OBJS): 	$(DIR_OBJS)%.o: %.c $(HEAD) Makefile | $(DIR_OBJS)
			$(CC) $(CFLAGS) $(ENV) -c $< -o $@ $(ALL_INC)
			@echo "$(_BOLD)$(_GREEN)--> $@ made$(_END)"

$(DIR_OBJS):
	mkdir -p $@

$(LIBFT): FORCE
	@echo "$(_BOLD)$(_GREEN)--> Creating $@...$(_END)"
	$(MAKE) -C $(LIBFT_DIR)
	@echo "$(_BOLD)$(_YELLOW)--> $@ made$(_END)"

compmlx:
	@echo "$(_BOLD)$(_GREEN)--> Creating MLX...$(_END)"
	$(MAKE) -C $(MLX_DIR)
	@echo "$(_BOLD)$(_YELLOW)--> MLX made $(_END)"

FORCE:

ci:
	rm bmp_saved/minirt_*

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	$(RM) -R $(DIR_OBJS)
	@echo "$(_BOLD)$(_RED)-> $@ made$(_END)"

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)
	@echo "$(_BOLD)$(_RED)-> $@ made$(_END)"

re: fclean
	$(MAKE)

.PHONY:		all exec clean fclean re bonus test compmlx ci
.SILENT:	$(OBJS) $(DIR_OBJS) $(NAME) $(LIBFT) compmlx

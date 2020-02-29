# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/13 14:56:19 by julnolle          #+#    #+#              #
#    Updated: 2020/02/29 14:30:47 by julnolle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minirt

CC		= clang

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
	MLX_DIR 	= ./minilibx/
	LDFLAGS		= -lmlx -lX11 -lXext -lm
else
	MLX_DIR 	= ./minilibx_opengl_20191021/
	LDFLAGS		= -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

# ---------------- SRC --------------- #

# Main Sources
SRCS += main.c
SRCS += minirt_utils.c 
SRCS += ft_vec_func_struct.c
SRCS += ft_set_env.c
SRCS += ft_set_obj.c
SRCS += minirt_forms.c
SRCS += raytracing.c
SRCS += ft_atof.c

# Gnl Sources
SRCS += get_next_line.c
SRCS += get_next_line_utils.c

vpath %.c srcs/
vpath %.c srcs/gnl/

#MAINTEST 	= test.c srcs/ft_set_env.c srcs/ft_atof.c
#TESTFILE 	=	scene.rt


# ---------------- INC --------------- #

INCLUDES 	=	./includes/
HEAD 		= $(INCLUDES)minirt.h
ALL_INC		=  -I$(INCLUDES) -I$(LIBFT_DIR) -I$(MLX_DIR)

# ---------------- OBJ --------------- #

DIR_OBJS	= ./objs/
OBJS		= $(patsubst %.c, $(DIR_OBJS)%.o, $(SRCS))
#OBJS_BONUS	= $(BONUS:.c=.o)

# ---------------- LIB --------------- #

## for libft compilation w/o chained list functions ##

LIBFT_DIR 	= libft/
LIBFT 		= $(LIBFT_DIR)libft.a
LIB_LINK	= $(LDFLAGS) -L$(LIBFT_DIR) -lft
####

all: $(NAME)

fast:
	$(MAKE) re -j8

$(NAME):	$(LIBFT) $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(ALL_INC) $(LIB_LINK) -o $@
			echo "\x1b[1m\x1b[33m-> Linking $@...\x1b[0m"

$(OBJS): 	$(DIR_OBJS)%.o: %.c $(HEAD) Makefile | $(DIR_OBJS)
			$(CC) $(CFLAGS) -c $< -o $@ $(ALL_INC)
			echo "\x1b[1m\x1b[32m-> $@ made\x1b[0m"

$(DIR_OBJS):
	mkdir -p $@

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)
	echo "\x1b[1m\x1b[31m--> Creating $@...\x1b[0m"

$(MLX):
	$(MAKE) -C $(MLX_DIR)
	echo "\x1b[1m\x1b[31m--> Creating $@...\x1b[0m"

FORCE:


# test:	$(HEAD) $(MAINTEST) $(LIBFT) $(GNL_SRCS)
# 			$(CC) -g $(MAINTEST) $(GNL_SRCS) $(LIBFT) -I$(INCLUDES) -I$(LIBFT_DIR) -o essai && ./essai $(TESTFILE)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) -R $(DIR_OBJS)
	echo "\x1b[1m\x1b[31m-> $@ made\x1b[0m"

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)
	echo "\x1b[1m\x1b[31m-> $@ made\x1b[0m"

re: fclean
	$(MAKE)

.PHONY:		all exec clean fclean re bonus test
.SILENT:	$(OBJS) $(NAME) $(LIBFT)
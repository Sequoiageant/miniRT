# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/13 14:56:19 by julnolle          #+#    #+#              #
#    Updated: 2020/03/04 16:35:21 by julnolle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include color.mk

NAME	= minirt

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
	MLX_DIR 	= ./minilibx/
	LDFLAGS		= -lmlx -lX11 -lXext -lm
	ENV			= -D LINUX
else
	MLX_DIR 	= ./minilibx_opengl_20191021/
	LDFLAGS		= -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	ENV			=
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
SRCS += color_utils.c

# Gnl Sources
SRCS += get_next_line.c

vpath %.c srcs/
vpath %.c srcs/gnl/

# ---------------- INC --------------- #

INCLUDES 	=	./includes/
HEAD 		= $(INCLUDES)minirt.h
ALL_INC		=  -I$(INCLUDES) -I$(LIBFT_DIR) -I$(MLX_DIR)

# ---------------- OBJ --------------- #

DIR_OBJS	= ./objs/
OBJS		= $(patsubst %.c, $(DIR_OBJS)%.o, $(SRCS))
#OBJS_BONUS	= $(BONUS:.c=.o)

# ---------------- LIB --------------- #

LIBFT_DIR 	= libft/
LIBFT 		= $(LIBFT_DIR)libft.a
LIB_LINK	= $(LDFLAGS) -L$(LIBFT_DIR) -lft

# --------- Compilation Rules -------- #

all: $(NAME)

fast:
	$(MAKE) re -j8

$(NAME):	$(LIBFT) $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(ALL_INC) $(LIB_LINK) -o $@
			echo "$(_BOLD)$(_YELLOW)-> Linking $@...$(_END)"

$(OBJS): 	$(DIR_OBJS)%.o: %.c $(HEAD) Makefile | $(DIR_OBJS)
			$(CC) $(CFLAGS) $(ENV) -c $< -o $@ $(ALL_INC)
			echo "$(_BOLD)$(_GREEN)-> $@ made$(_END)"

$(DIR_OBJS):
	mkdir -p $@

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)
	echo "$(_BOLD)$(_RED)--> $@ made$(_END)"

$(MLX):
	$(MAKE) -C $(MLX_DIR)
	echo "$(_BOLD)$(_RED)--> Creating $@...$(_END)"

FORCE:

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) -R $(DIR_OBJS)
	@echo "$(_BOLD)$(_RED)-> $@ made$(_END)"

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)
	@echo "$(_BOLD)$(_RED)-> $@ made$(_END)"

re: fclean
	$(MAKE)

.PHONY:		all exec clean fclean re bonus test
.SILENT:	$(OBJS) $(DIR_OBJS) $(NAME) $(LIBFT)
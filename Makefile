# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/13 14:56:19 by julnolle          #+#    #+#              #
#    Updated: 2020/02/13 19:33:55 by julnolle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	a.out

SRCS	= 	srcs/main.c \
			srcs/minirt_utils.c srcs/ft_set_env.c srcs/ft_vec_func.c \
			srcs/minirt_forms.c srcs/raytracing.c \
			srcs/ft_atof.c

GNL_SRCS	= 	srcs/gnl/get_next_line.c srcs/gnl/get_next_line_utils.c

MAINTEST 	=	test.c

TESTFILE 	=	scene.rt

INCLUDES 	=	./includes

LMX_DIR 	=	./minilibx_opengl_20191021

LINUX_LMX 	=	./minilibx

HEAD 		= $(INCLUDES)/minirt.h

OBJS		= $(SRCS:.c=.o)

OBJS_BONUS	= $(BONUS:.c=.o)

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

LDFLAGS		= -L. -lftprintf

SANITIZE	= -g

LDFLAGS		= -L $(LMX_DIR) -lmlx

LMX_FLAGS	= -framework OpenGL -framework AppKit

LINUXFLAGS	= -lmlx -lX11 -lXext -lm 
## for libft compilation w/o chained list functions ##
LIBFT_DIR 	= libft/
LIBFT 		= $(LIBFT_DIR)libft.a
####


all:	$(NAME)

$(LIBFT):
		@echo "\x1b[1m\x1b[31m--> Compiling Libft...\x1b[0m"
		@(cd $(LIBFT_DIR) && $(MAKE))

$(MLX):
		@echo "\x1b[1m\x1b[31m--> Compiling mlx...\x1b[0m"
		@(cd $(LMX_DIR) && $(MAKE))

$(NAME):	$(HEAD) $(SRCS) $(GNL_SRCS) $(MLX) $(LIBFT)
			$(CC) $(SRCS) $(GNL_SRCS) $(LIBFT) -I$(INCLUDES) -I$(LMX_DIR) -I$(LIBFT_DIR) $(LINUXFLAGS)

test:	$(HEAD) $(MAINTEST) $(LIBFT) $(GNL_SRCS)
			$(CC) $(MAINTEST) $(GNL_SRCS) $(LIBFT) -I$(INCLUDES) -I$(LIBFT_DIR) -o essai && ./essai $(TESTFILE)

# $(OBJS):	%.o: %.c $(HEAD)
# 			$(CC) -c -I $(INCLUDES) -I $(LMX_DIR) $(SANITIZE) $(LDFLAGS) $(LMX_FLAGS) $< -o $@
# 			@echo "\x1b[1m\x1b[32m-> $@ compiled\x1b[0m"
clean:
	@(cd $(LIBFT_DIR) && $(MAKE) $@)
	@$(RM) $(OBJS)
	@echo "\x1b[1m\x1b[31m-> $@ made\x1b[0m"

fclean: clean
	@(cd $(LIBFT_DIR) && $(MAKE) $@)
	@$(RM) $(NAME)
	@echo "\x1b[1m\x1b[31m-> $@ made\x1b[0m"

re: fclean all

.PHONY:		all exec clean fclean re bonus test

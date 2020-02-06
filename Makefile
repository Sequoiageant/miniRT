# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/13 14:56:19 by julnolle          #+#    #+#              #
#    Updated: 2020/02/06 15:53:38 by julnolle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	a.out

SRCS	= 	main.c \
			srcs/minirt_utils.c srcs/ft_set_env.c \
			srcs/gnl/get_next_line.c srcs/gnl/get_next_line_utils.c \
			srcs/minirt_forms.c srcs/raytracing.c \
			srcs/ft_atof.c

TESTFILE 	=	scene.rt

INCLUDES 	=	./includes

MINIDIR 	=	./minilibx_opengl_20191021

HEAD 		= $(INCLUDES)/minirt.h

OBJS		= $(SRCS:.c=.o)

OBJS_BONUS	= $(BONUS:.c=.o)

CC			= clang

CFLAGS		= -Wall -Wextra -Werror

LDFLAGS		= -L. -lftprintf

SANITIZE	= -g

LDFLAGS		= -L $(MINIDIR) -l mlx

MINIFLAGS	= -framework OpenGL -framework AppKit

## for libft compilation w/o chained list functions ##
LIBFT_DIR 	= libft/
LIBFT 		= $(LIBFT_DIR)libft.a
####


all:	$(NAME)

$(LIBFT):
		@echo "\x1b[1m\x1b[31m--> Compiling Libft...\x1b[0m"
		@(cd $(LIBFT_DIR) && $(MAKE))

$(NAME):	$(HEAD) $(SRCS) $(TESTFILE) $(LIBFT)
			$(CC) $(CFLAGS) -I $(INCLUDES) -I $(MINIDIR) $(LDFLAGS) $(MINIFLAGS) $(SRCS) $(LIBFT) -I $(LIBFT_DIR)

# $(OBJS):	%.o: %.c $(HEAD)
# 			$(CC) -c -I $(INCLUDES) -I $(MINIDIR) $(SANITIZE) $(LDFLAGS) $(MINIFLAGS) $< -o $@
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

.PHONY:		all exec clean fclean re bonus

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/13 14:56:19 by julnolle          #+#    #+#              #
#    Updated: 2020/01/24 16:34:07 by julnolle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	a.out

SRCS	= 	main.c \
			srcs/utils/minirt_utils.c \
			srcs/gnl/get_next_line.c srcs/gnl/get_next_line_utils.c

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


all:	$(NAME)

$(NAME):	$(HEAD) $(SRCS) $(TESTFILE)
			$(CC) -I $(INCLUDES) -I $(MINIDIR) $(SANITIZE) $(LDFLAGS) $(MINIFLAGS) $(SRCS)

# $(OBJS):	%.o: %.c $(HEAD)
# 			$(CC) -c -I $(INCLUDES) -I $(MINIDIR) $(SANITIZE) $(LDFLAGS) $(MINIFLAGS) $< -o $@
# 			@echo "\x1b[1m\x1b[32m-> $@ compiled\x1b[0m"
clean:
	@$(RM) $(OBJS)
	@echo "\x1b[1m\x1b[31m-> $@ made\x1b[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\x1b[1m\x1b[31m-> $@ made\x1b[0m"

re: fclean all

.PHONY:		all exec clean fclean re bonus

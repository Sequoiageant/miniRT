# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/10 13:56:26 by julnolle          #+#    #+#              #
#    Updated: 2020/04/30 16:30:54 by julnolle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror

# ---------------- COL --------------- #

red			= \033[1;31m
green		= \033[1;32m
yellow		= \033[1;33m
no_color	= \033[1;0m

# ---------------- SRC --------------- #

# Main Sources

SRCS	+= 	ft_putchar_fd.c
SRCS	+= 	ft_putstr_fd.c
SRCS	+= 	ft_putnbr_fd.c
SRCS	+= 	ft_strlen.c
SRCS	+= 	ft_nbrsize.c
SRCS	+= 	ft_isdigit.c
SRCS	+= 	ft_atoi.c
SRCS	+= 	ft_atof.c
SRCS	+= 	ft_split.c
SRCS	+= 	ft_split_whitespaces.c
SRCS	+= 	ft_strcmp.c
SRCS	+= 	ft_memcpy.c
SRCS	+= 	ft_itoa.c
SRCS	+= 	ft_bzero.c
SRCS	+= 	ft_strdup.c
SRCS	+= 	ft_strjoin.c
SRCS	+= 	ft_strjoin_back.c
SRCS	+= 	ft_substr.c

# For debug
SRCS	+= 	ft_putchar.c
SRCS	+= 	ft_putendl.c
SRCS	+= 	ft_putstr.c
SRCS	+= 	ft_putnbr.c

# Bonus Sources
# [...]

vpath %.c .

# ---------------- INC --------------- #

INCLUDES =	./
HEAD = $(INCLUDES)libft.h

# ---------------- OBJ --------------- #

DIR_OBJS	= ./objs/
OBJS		= $(patsubst %.c, $(DIR_OBJS)%.o, $(SRCS))
OBJS_BONUS	= $(patsubst %.c, $(DIR_OBJS)%.o, $(BONUS))


# --------- Compilation Rules -------- #

all:		$(NAME)

$(NAME):	$(OBJS)
			ar rcs $@ $^
			ranlib $(NAME)
			echo "$(yellow)--> Creating $@...$(no_color)"

$(OBJS): 	$(DIR_OBJS)%.o: %.c $(HEAD) Makefile | $(DIR_OBJS)
			$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDES)

bonus : 	$(OBJS) $(OBJS_BONUS)
			ar rcs $(NAME) $^
			ranlib $(NAME)
			echo "$(yellow)--> Creating $@...$(no_color)"

$(OBJS_BONUS):	$(DIR_OBJS)%.o: %.c $(HEAD)
				$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDES)

$(DIR_OBJS):
	mkdir -p $@

clean:
			$(RM) -R $(DIR_OBJS)
			echo "$(red)-> $@ libft made$(no_color)"

fclean:		clean
			$(RM) $(NAME)

re: 		fclean
			$(MAKE)

.PHONY:		all clean fclean re bonus coffee music
.SILENT:	$(OBJS) $(NAME) clean

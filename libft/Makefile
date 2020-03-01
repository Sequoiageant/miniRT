# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julnolle <julnolle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/10 13:56:26 by julnolle          #+#    #+#              #
#    Updated: 2020/02/13 18:59:44 by julnolle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

# ---------------- COL --------------- #

red			= \033[1;31m
green		= \033[1;32m
yellow		= \033[1;33m
no_color	= \033[1;0m

SRCS	= 	ft_putchar.c ft_strlen.c ft_putstr.c ft_putendl.c ft_putnbr.c \
			ft_atoi.c ft_split2.c ft_strcmp.c \
			ft_strdup.c ft_memcpy.c

BONUS	=	ft_lstadd_back.c ft_lstlast.c ft_lstadd_front.c \
			ft_lstsize.c ft_lstnew.c \
			ft_lstiter.c ft_lstdelone.c ft_lstclear.c ft_lstmap.c 

INCLUDES =	./

HEAD = $(INCLUDES)libft.h

OBJS	=	$(SRCS:.c=.o)

OBJS_BONUS	=	$(BONUS:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror



all:		$(NAME)

$(NAME):	$(OBJS)
			ar rcs $@ $^
			ranlib $(NAME)
			echo "$(red)--> Creating $@...$(no_color)"

$(OBJS):	%.o: %.c $(HEAD)
			$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDES)

bonus : 	$(OBJS_BONUS) $(OBJ)
			ar rcs $(NAME) $^
			ranlib $(NAME)
			echo "$(red)--> Creating $@...$(no_color)"

$(OBJS_BONUS):	%.o: %.c $(HEAD)
			$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDES)

clean:
			$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
		   	$(RM) $(NAME)

re:			fclean all

.SILENT:	$(OBJS) $(NAME)

coffee:
	@echo ""
	@echo "             (         ) "
	@echo "	              )        ("
	@echo "               ___)...----)----....___"
	@echo '           .-""      )    (           ""-.'
	@echo "      .-''''|-._      (       )        _.-|"
	@echo '     /  .--.|   `""---...........---""`   |'
	@echo "    /  /    |                             |"
	@echo "    |  |    |                             |"
	@echo "     \  \   |                             |"
	@echo "      '\ '\ |                             |"
	@echo "        '\ '|                             |"
	@echo "        _/ /\                             /"
	@echo "       (__/  \                           /"
	@echo '    _..---""` \                         /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._                '"--...___...--"'              _.'"
	@echo '   \""--..__                              __..--""/'
	@echo "     '._     """----.....______.....----"""         _.'"
	@echo '         ""--..,,_____            _____,,..--"""'''
	@echo '                      """------"""'

music:
	@echo ""                      	  
	@echo "						  .     	"
	@echo "		                      .   |     	"
	@echo "		   _.-._              |  0'     	"
	@echo "		 ,'     '.__,--.     0'         	"
	@echo "		/   .--.        |           ,,, 	"
	@echo "		| [==========|=|=|=|=|==|==_- -]	"
	@echo "		\   "--" __ .   |           ''' 	"
	@echo "		 '..__.,'   '--'                	"
	@echo "		   		    .   .0    . 	       	"
	@echo "		jn          |)  |)   .|     	   	"
	@echo "		  ____     0'   '   | 0 	       	"
	@echo "		  |  |             0'           	"
	@echo "		 0' 0'								"

.PHONY:		all clean fclean re bonus coffee music

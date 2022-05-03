# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 15:37:42 by modysseu          #+#    #+#              #
#    Updated: 2022/03/29 20:27:39 by modysseu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRC		=	init_list.c\
			list_func.c\
			utils.c\
			parser.c\
			thread_func.c\
			executoin.c\
			execution_utils.c\
			main.c

HEADER	=	philosophers.h

CC		=	cc

FLAGS	=	-Werror -Wall -Wextra -I $(HEADER) -xinstrument=datarace
#leaks --atExit --
#-fsanitize=address -g
#-fsanitize=thread -g
RM		=	rm -f

OBJ		= $(SRC:.c=.o)

all		:	$(NAME)

$(NAME) : $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER) Makefile
	$(CC) $(FLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re

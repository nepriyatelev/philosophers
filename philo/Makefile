# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 15:37:42 by modysseu          #+#    #+#              #
#    Updated: 2022/03/16 19:37:18 by modysseu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRC		=	ft_atoi.c\
			ft_isdigit.c\
			main.c

HEADER	=	philosophers.h

CC		=	cc

FLAGS	=	-Werror -Wall -Wextra -g -I $(HEADER) -pthread

RM		=	rm -f

OBJ		= $(SRC:.c=.o)

all		:	$(NAME)

$(NAME) : $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

# %.o: %.c $(HEADER) Makefile
# 	$(CC) $(FLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
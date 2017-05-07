#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: ttshivhu <ttshivhu@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2017/05/07 09:22:09 by ttshivhu          #+#    #+#             *#
#*   Updated: 2017/05/07 09:43:40 by ttshivhu         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

HEADER  = src/snake.h

SRC	= src/snake.c \
	  src/keyhandler.c 

NAME	= snake

OBJ	= $(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc $(HEADER) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 15:15:02 by mmosca            #+#    #+#              #
#    Updated: 2022/07/12 17:22:57 by mmosca           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			=	$(shell find ./tests -type f -name "*.cpp" | cut -c 3-)
HEADER		=	$(shell find ./includes -type f -name "*.hpp" | cut -c 3-)

OBJ			=	$(SRC:.cpp=.o)

CC			=	c++
FLAGS		=	-Wall -Werror -Wextra -std=c++98
FLAGS_H		=	-Iincludes/
NAME		=	ft_containers

all: $(NAME)

%.o: %.cpp $(HEADER)
	$(CC) $(FLAGS) $(FLAGS_H) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(FLAGS_H) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	fclean
	$(MAKE) all

.PHONY: all clean fclean re

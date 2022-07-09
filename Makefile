# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 15:15:02 by mmosca            #+#    #+#              #
#    Updated: 2022/07/09 15:15:53 by mmosca           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BBLU		=	\033[1;34m
BGREEN		=	\033[1;32m
BRED		=	\033[1;31m
BLU			=	\033[0;34m
GRN			=	\033[0;32m
RED			=	\033[0;31m
RST			=	\033[0m

SRC			=	$(shell find ./tests -type f -name "*.cpp" | cut -c 3-)
HEADER		=	$(shell find ./includes -type f -name "*.hpp" | cut -c 3-)

OBJ			=	$(SRC:.cpp=.o)

CC			=	c++
FLAGS		=	-Wall -Werror -Wextra -std=c++98
FLAGS_H		=	-Iincludes/
NAME		=	ft_containers

all: $(NAME)
.PHONY: all

print_header:
	echo "\033[1;34m\033[5G========================================================================================================"
	echo "\033[1;34m\033[5G"
	echo "\033[1;34m\033[5G███████╗████████╗      ██████╗ ██████╗ ███╗   ██╗████████╗ █████╗ ██╗███╗   ██╗███████╗██████╗ ███████╗"
	echo "\033[1;34m\033[5G██╔════╝╚══██╔══╝     ██╔════╝██╔═══██╗████╗  ██║╚══██╔══╝██╔══██╗██║████╗  ██║██╔════╝██╔══██╗██╔════╝"
	echo "\033[1;34m\033[5G█████╗     ██║        ██║     ██║   ██║██╔██╗ ██║   ██║   ███████║██║██╔██╗ ██║█████╗  ██████╔╝███████╗"
	echo "\033[1;34m\033[5G██╔══╝     ██║        ██║     ██║   ██║██║╚██╗██║   ██║   ██╔══██║██║██║╚██╗██║██╔══╝  ██╔══██╗╚════██║"
	echo "\033[1;34m\033[5G██║        ██║███████╗╚██████╗╚██████╔╝██║ ╚████║   ██║   ██║  ██║██║██║ ╚████║███████╗██║  ██║███████║"
	echo "\033[1;34m\033[5G╚═╝        ╚═╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝╚══════╝"
	echo "\033[1;34m\033[5G"
	echo "\033[1;34m\033[5G=======================================> By mmosca <===================================================="
.PHONY: print_header

%.o: %.cpp $(HEADER)
	$(CC) $(FLAGS) $(FLAGS_H) -c $< -o $@
	echo "$(BBLU)[$(NAME) OBJ] :$(RST) $@ $(BGREEN)\033[47G[✔]$(RST)"

$(NAME): print_header $(OBJ)
	$(CC) $(FLAGS) $(FLAGS_H) $(OBJ) -o $(NAME)
	echo "$(BGREEN)[$(NAME) END] :$(RST)$(RST) ./$(NAME) $(BGREEN)\033[47G[✔]$(RST)"

test: all
	./$(NAME)

clean:
	rm -f $(OBJ)
	echo "$(RED)[CLEAN]  :$(RST) Deleting objects...$(BGREEN)\033[47G[✔]$(RST)"
.PHONY: clean

fclean: clean
	rm -f $(NAME)
	echo "$(RED)[FCLEAN] :$(RST) Deleting executable...$(BGREEN)\033[47G[✔]$(RST)"
.PHONY: fclean

re:	fclean all
.PHONY: re

.SILENT:

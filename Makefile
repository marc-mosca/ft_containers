# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 13:14:43 by mmosca            #+#    #+#              #
#    Updated: 2022/07/05 11:14:20 by mmosca           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##	~~	Properties -------------------------------------------------------------

NAME		:=	ft_containers
INCS_DIR	:=	includes
SRCS_DIR	:=	sources
OBJS_DIR	:=	.objs
CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98
VPATH		:=	$(SRCS_DIR)/:
SRCS		:=	main.cpp
OBJS		:=	$(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))

##	~~	Rules ------------------------------------------------------------------

.PHONY: all clean fclean re

##	~	Main rules ---------------------

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

re: fclean all

##	~	Compilations rules -------------

$(OBJS): | $(OBJS_DIR)

$(OBJS_DIR):
	mkdir -p $@

$(OBJS_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

##	~	Cleaning rules -----------------

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

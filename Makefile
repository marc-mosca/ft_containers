# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/18 13:03:38 by mmosca            #+#    #+#              #
#    Updated: 2022/06/18 13:16:25 by mmosca           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

##	~~	Properties -------------------------------------------------------------

NAME		:=	ft_containers
INCS_DIR	:=	incs
SRCS_DIR	:=	srcs
OBJS_DIR	:=	.objs
CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98
VPATH		:=	$(SRCS_DIR)/:$(SRCS_DIR)/containers:$(SRCS_DIR)/tools:
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

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/27 17:20:20 by emohamed          #+#    #+#              #
#    Updated: 2023/09/28 07:56:12 by emohamed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = ft_malloc.a

FLAGS = -Wall -Werror -Wextra

CC = cc

GREEN = \033[0;32m
RESET = \033[0m

SOURCES = $(addprefix ./, ft_malloc.c misc_functions.c misc_functions2.c)

INCLUDE = ft_malloc.h

all: $(NAME) $(SOURCES)

$(NAME): $(SOURCES:.c=.o) $(INCLUDE)
	ar -r $(NAME) $(SOURCES:.c=.o)

%.o: %.c
	@$(CC) $(FLAGS) -I $(INCLUDE) -c $<
	@echo "$(GREEN)✅ Compiled: $<$(RESET)"

clean:
	@rm -rf $(SOURCES:.c=.o)
	@echo "$(GREEN)✅ Cleaned up object files$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(GREEN)✅ Cleaned up $(NAME)$(RESET)"

re: fclean all

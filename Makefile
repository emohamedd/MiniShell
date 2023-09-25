# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 15:27:28 by emohamed          #+#    #+#              #
#    Updated: 2023/09/25 12:53:17 by emohamed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
#CFLAGS = -g -fsanitize=address
LDFLAGS = -lreadline 
RLFLGS = -L/Users/emohamed/.brew/opt/readline/lib -lreadline
RLOFLGS = -I/Users/emohamed/.brew/opt/readline/include

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

NAME = minishell

GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(RLOFLGS) -c $< -o $@
	@echo "$(GREEN)✅ Compiled: $<$(RESET)"

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME) $(LDFLAGS) $(RLFLGS)
	@echo "$(GREEN)✅  MINISHELL : Compilation successful!$(RESET)"

clean:
	@make -C libft/ fclean
	@rm -f $(OBJS)
	@echo "$(GREEN)✅ Cleaned up object files$(RESET)"

fclean: clean
	@make -C libft/ fclean
	@rm -f $(NAME)
	@echo "$(GREEN)✅ Cleaned up $(NAME)$(RESET)"

re: fclean all

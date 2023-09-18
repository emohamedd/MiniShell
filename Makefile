# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 15:27:28 by emohamed          #+#    #+#              #
#    Updated: 2023/09/18 10:17:16 by emohamed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -I./includes
NAME = minishell
READLINE = -L/Users/emohamed/.brew/opt/readline/lib -I/Users/emohamed/.brew/opt/readline/include
LIBFT = -L./libft -lft

RLFLGS = -L/Users/emohamed/.brew/opt/readline/lib -lreadline
RLOFLGS = -I/Users/emohamed/.brew/opt/readline/include

SRCS = cd.c echo.c env.c exec_cmds.c export.c ft_split_token.c ft_strdup.c ft_strlen.c herdo_parse.c make_tokens.c minishell.c pipes.c print_table.c read_input.c redirection.c run_code.c syntax_err.c token.c unset.c
OBJS = $(SRCS:.c=.o)

GREEN = \033[0;32m
RESET = \033[0m

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C libft all
	@echo "$(GREEN)✅ MINISHELL : Compilation successful!$(RESET)"
	@$(CC) $(CFLAGS) $(LIBFT) $(RLFLGS) $^ -o $@

%.o: %.c
	@$(CC) $(CFLAGS) $(RLOFLGS) -c $< -o $@
	@echo "$(GREEN)✅ Compiled: $<$(RESET)"

clean:
	@make -C libft clean
	@rm -f $(OBJS)
	@echo "$(GREEN)✅ Cleaned up object files$(RESET)"

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	@echo "$(GREEN)✅ Cleaned up executable$(RESET)"

re: fclean all

run: all
	@./$(NAME)

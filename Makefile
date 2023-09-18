# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 15:27:28 by emohamed          #+#    #+#              #
#    Updated: 2023/09/18 11:13:27 by emohamed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -I./includes #-g -fsanitize=address
NAME = minishell
READLINE = -L/Users/emohamed/.brew/opt/readline/lib -I/Users/emohamed/.brew/opt/readline/include
LIBFT = -L./libft -lft

RLFLGS = -L/Users/emohamed/.brew/opt/readline/lib -lreadline
RLOFLGS = -I/Users/emohamed/.brew/opt/readline/include

SRCS =cd.c echo.c env.c exec_cmds.c export.c fell_env_struct.c fill_commands.c from_2d_to_one.c ft_get_env.c ft_split_token.c ft_strdup.c ft_strlen.c get_cmds.c herdo_parse.c make_tokens.c minishell.c pipes.c print_table.c read_input.c redirection.c run_code.c signal_handler.c syntax_err.c token.c unset.c
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

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 15:27:28 by emohamed          #+#    #+#              #
#    Updated: 2023/10/01 01:06:23 by emohamed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline 
RLFLGS = -L/Users/emohamed/.brew/opt/readline/lib -lreadline #-fsanitize=address
RLOFLGS = -I/Users/emohamed/.brew/opt/readline/include

SRCS = alloca_start_end.c allocat_token.c allocation_export.c builtins.c cd.c echo.c env.c exec_cmds.c exit.c expand_double_quotes.c expand_single_quotes.c expand_var.c export.c export_link.c fell_env_struct.c fell_export.c fill_commands.c from_2d_to_one.c ft_get_env.c ft_strcmp.c ft_strdup.c ft_strjoin_export.c ft_strlen.c ft_strndup.c get_cmds.c giga_split.c giga_split_utils.c has_redirections.c herdo_parse.c herdoc_utils.c is_char.c lenght_of_2d.c make_tokens.c minishell.c pipes.c read_input.c redirection.c redirection_types.c run_cmds.c run_code.c signal_handler.c syntax_err.c the_var_state.c unset.c variable_size.c
OBJS = $(SRCS:.c=.o)

NAME = minishell

GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(RLOFLGS) -c $< -o $@
	@echo "$(GREEN)✅ Compiled: $<$(RESET)"

$(NAME): $(OBJS)
	@make -C malloc
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS)  malloc/ft_malloc.a libft/libft.a -o $(NAME) $(LDFLAGS) $(RLFLGS)
	@echo "$(GREEN)✅  MINISHELL : Compilation successful!$(RESET)"

clean:
	@make -C malloc/ clean
	@make -C libft/ clean
	@rm -f $(OBJS)
	@echo "$(GREEN)✅ Cleaned up object files$(RESET)"

fclean: clean
	@make -C malloc/ fclean
	@make -C libft/ fclean
	@rm -f $(NAME)
	@echo "$(GREEN)✅ Cleaned up $(NAME)$(RESET)"

re: fclean all

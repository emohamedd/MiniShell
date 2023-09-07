# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 15:27:28 by emohamed          #+#    #+#              #
#    Updated: 2023/09/07 18:56:12 by haarab           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g
LDFLAGS = -lreadline

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

NAME = minishell

all: $(NAME)

%.o: %.c
	make -C libft
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a  -o $(NAME) $(LDFLAGS)

clean:
	make -C libft/ fclean
	rm -f $(OBJS)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all

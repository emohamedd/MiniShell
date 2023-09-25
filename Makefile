# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 15:27:28 by emohamed          #+#    #+#              #
#    Updated: 2023/09/24 17:46:23 by haarab           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
#CFLAGS = -g -fsanitize=address
LDFLAGS = -lreadline 
RLFLGS = -L/Users/haarab/.brew/opt/readline/lib -lreadline
RLOFLGS = -I/Users/haarab/.brew/opt/readline/include

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

NAME = minishell

all: $(NAME)

%.o: %.c
	make -C libft
	$(CC) $(CFLAGS) $(RLOFLGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a  -o $(NAME) $(LDFLAGS)  $(RLFLGS)

clean:
	make -C libft/ fclean
	rm -f $(OBJS)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all
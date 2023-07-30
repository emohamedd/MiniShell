# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emohamed <emohamed@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 15:27:28 by emohamed          #+#    #+#              #
#    Updated: 2023/07/30 14:29:13 by emohamed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
SRCS = *.c
OBJS = $(SRCS:.c=.o)

NAME = minishell.a

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

$(NAME): $(OBJS) 
	ar -rcs $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

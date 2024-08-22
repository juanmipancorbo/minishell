# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/22 17:58:31 by jpancorb          #+#    #+#              #
#    Updated: 2024/08/22 19:23:40 by jpancorb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC_FILES 	= main.c parser.c tokenizer.c
SRCS		= $(addprefix src/, $(SRC_FILES))
OBJS		= $(patsubst src/%.c, obj/%.o, $(SRCS))

HEADER		= include/minishell.h

LIBFT		= libft/libft.a

CFLAGS		= -Wall -Werror -Wextra 
LDFLAGS		= -lreadline -Llibft -lft

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		cc $(CFLAGS) -o $@ $^ $(LDFLAGS)

obj/%.o: src/%.c $(HEADER)
		mkdir -p obj
		cc $(CFLAGS) -c $< -o $@

$(LIBFT):
		make -C libft

clean:
		rm -f obj/*.o
		make -C libft clean

fclean: clean
		rm -f $(NAME)
		rm -rf obj
		make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
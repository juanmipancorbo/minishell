# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/22 17:58:31 by jpancorb          #+#    #+#              #
#    Updated: 2024/08/29 19:19:32 by jpancorb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC_FILES 	= main.c tokenizer_1.c tokenizer_2.c utils.c##parser.c 
SRCS		= $(addprefix src/, $(SRC_FILES))
OBJS		= $(patsubst src/%.c, obj/%.o, $(SRCS))
MODE		= none
HEADER		= include/minishell.h

LIBFT		= libft/libft.a

CFLAGS		= -g -Wall -Werror -Wextra
LDFLAGS		= -lreadline -Llibft -lft

ifeq ($(MODE),debug)
	CFLAGS += -fsanitize=leak -g
endif

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		cc $(CFLAGS) -o $@ $^ $(LDFLAGS)

obj/%.o: src/%.c $(HEADER)
		@mkdir -p obj
		cc $(CFLAGS) -c $< -o $@

$(LIBFT):
		make --silent -C libft

clean:
		rm -f obj/*.o
		make --silent -C libft clean

fclean: clean
		rm -f $(NAME)
		rm -rf obj
		make --silent -C libft fclean

re: fclean all

.PHONY: all clean fclean re
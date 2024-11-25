
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/22 17:58:31 by jpancorb          #+#    #+#              #
#    Updated: 2024/09/18 20:06:59 by jpancorb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC_FILES 	= a_built_in_utils.c a_exec_utils.c a_ft_env.c a_heredoc.c\
			a_pipes_fn.c env_variables.c expander.c expander_utils_2.c ft_cd.c\
			ft_exit.c ft_unset.c main.c no_env.c parser_2.c parser_4.c\
			tokenizer_1.c utils_1.c utils_3.c utils_5.c a_execute.c\
			a_exit_fn.c a_ft_pwd.c a_list_fn.c a_signal.c errors_fn.c\
			expander_utils_1.c file_descriptors.c ft_echo.c ft_export.c\
			heredoc_utils.c merger.c parser_1.c parser_3.c parser_utils_1.c\
			tokenizer_2.c utils_2.c utils_4.c parser_utils_2.c parser_utils_3.c

SRCS		= $(addprefix src/, $(SRC_FILES))
OBJS		= $(patsubst src/%.c, obj/%.o, $(SRCS))
HEADER		= include/minishell.h
MODE		= none

LIBFT		= libft/libft.a

CFLAGS		= -Wall -Werror -Wextra
LDFLAGS		= -lreadline -Llibft -lft

ifeq ($(MODE),debug)
	CFLAGS += -g -fsanitize=leak
endif

ifeq ($(MODE),noflag)
	CFLAGS = -g
endif

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		cc $(CFLAGS) -o $@ $^ $(LDFLAGS)

obj/%.o: src/%.c $(HEADER) Makefile
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
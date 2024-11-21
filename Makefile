
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

SRC_FILES 	= main.c tokenizer_1.c tokenizer_2.c utils.c parser_1.c parser_2.c\
            parser_3.c expander.c parsing_utils.c env_variables.c utils_2.c\
            a_execute.c errors_fn.c file_descriptors.c a_list_fn.c parsing_test.c\
            a_heredoc.c  a_exit_fn.c utils_4.c a_pipes_fn.c ft_cd.c\
            a_built_in_utils.c ft_echo.c a_ft_env.c ft_exit.c a_signal.c\
            ft_export.c a_ft_pwd.c ft_unset.c expander_utils.c utils_3.c\
            ft_export.c a_ft_pwd.c ft_unset.c expander_utils.c utils_3.c no_env.c\
			a_exec_utils.c heredoc_utils.c expander_utils_2.c utils_5.c

SRCS		= $(addprefix src/, $(SRC_FILES))
OBJS		= $(patsubst src/%.c, obj/%.o, $(SRCS))
HEADER		= include/minishell.h
MODE		= none

LIBFT		= libft/libft.a

CFLAGS		= -Wall -Werror -Wextra -g
LDFLAGS		= -lreadline -Llibft -lft

ifeq ($(MODE),debug)
	CFLAGS += -g -fsanitize=address
endif

ifeq ($(MODE),noflag)
	CFLAGS = -g -fsanitize=address
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
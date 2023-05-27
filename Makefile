# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/21 17:46:55 by ochouikh          #+#    #+#              #
#    Updated: 2023/05/25 18:07:02 by mel-aini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

HEADERS = minishell.h libft/libft.h ft_printf/ft_printf.h libft/get_next_line.h build_tree/build_tree.h builtins/builtins.h execution/execution.h expander/expander.h here_doc/here_doc.h linked_list/linked_list.h parsing/parsing.h tokenization/tokenization.h

SRC = minishell.c builtins/ft_envdup.c builtins/echo.c builtins/cd.c builtins/cd_utils.c builtins/pwd.c builtins/export.c builtins/export_unset_utils_1.c builtins/export_unset_utils_2.c builtins/env.c builtins/unset.c builtins/exit.c builtins/ft_max.c \
	linked_list/ft_lstnew.c linked_list/ft_lstadd_front.c linked_list/ft_lstsize.c linked_list/ft_lstlast.c linked_list/ft_lstadd_back.c linked_list/ft_lstdelone.c linked_list/ft_lstclear.c linked_list/pipe_lstnew.c linked_list/pipe_lstadd_back.c \
	tokenization/tokenization.c tokenization/expand_tokens.c tokenization/expand_tokens_utils.c tokenization/tokenization_utils.c parsing/parsing.c parsing/parsing_utils.c parsing/check_parens.c parsing/errors.c \
	build_tree/build_tree.c build_tree/build_tree_utils.c build_tree/ft_tree_add_new.c build_tree/ft_tree_add_root.c build_tree/ft_tree_add_right.c build_tree/ft_tree_add_left.c \
	here_doc/here_doc.c here_doc/here_doc_utils.c execution/traverse_tree.c execution/traverse_tree_utils.c execution/run_execve.c execution/execution_utils.c execution/redirections.c execution/builtin_utils.c \
	expander/expander.c expander/expander_utils.c expander/wildcard.c expander/wildcard_utils.c expander/wildcard_utils2.c expander/expand_heredoc.c expander/expand_heredoc_utils.c \
	libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c libft/ft_isascii.c libft/ft_isprint.c libft/ft_strlen.c \
	libft/ft_memset.c libft/ft_bzero.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_strlcpy.c libft/ft_strlcat.c libft/ft_toupper.c \
	libft/ft_tolower.c libft/ft_strchr.c libft/ft_strrchr.c libft/ft_strncmp.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_strnstr.c \
	libft/ft_atoi.c libft/ft_calloc.c libft/ft_strdup.c libft/ft_substr.c libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_split.c \
	libft/ft_itoa.c libft/ft_strmapi.c libft/ft_striteri.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_putendl_fd.c \
	libft/ft_putnbr_fd.c libft/get_next_line.c libft/get_next_line_utils.c \
	ft_printf/ft_printf.c ft_printf/ft_putchar.c ft_printf/ft_putstr.c ft_printf/ft_putnbr.c ft_printf/ft_putnbr_unsigned.c ft_printf/ft_putnbr_base.c ft_printf/ft_putadr.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

READLINE_PATH=$(shell brew --prefix readline)

all: $(NAME)

$(NAME): $(OBJ)
	cc $(FLAGS) -L $(READLINE_PATH)/lib -lreadline $(OBJ) -o $(NAME)

%.o: %.c $(HEADERS)
	cc $(FLAGS) -I $(READLINE_PATH)/include -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


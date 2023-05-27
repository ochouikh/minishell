/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:51:28 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/25 15:07:45 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "ft_printf/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "tokenization/tokenization.h"
# include "parsing/parsing.h"
# include "here_doc/here_doc.h"
# include "build_tree/build_tree.h"
# include "builtins/builtins.h"
# include "execution/execution.h"
# include "expander/expander.h"
# include "linked_list/linked_list.h"
# include <dirent.h>

int	g_exit_status;

typedef enum e_type {
	SP,
	WORD,
	WILDCARD,
	QUOTE,
	DOLLAR,
	Q_DOLLAR,
	D_QUOTE,
	QUOTES,
	GREAT,
	D_GREAT,
	LESS,
	D_LESS,
	L_PAREN,
	R_PAREN,
	PIPE,
	AND,
	OR,
	ENV
}				t_type;

typedef struct s_info {
	t_tree	*tree;
	char	*line;
	int		if_wait;
	int		in;
	int		out;
	int		opened_paren;
	int		invalid_input;
	t_list	*env;
	t_list	*heredoc_files;
	t_list	*export;
	t_list	*tokens;
	t_list	*new_list;
}				t_info;

#endif

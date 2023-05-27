/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:15:39 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/18 21:36:35 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"

typedef struct s_list	t_list;
typedef struct s_tree	t_tree;
typedef struct s_info	t_info;

int		parsing(t_list **tokens, t_info *infos, int status);
void	ft_lstdelnode(t_list **list);

int		check_redirections(t_list **ptr, char *tmp_data);
int		check_quotes(t_list **ptr, char *tmp_data, t_list **head);
int		check_parens(t_list **ptr, int *checked, t_info *infos, char *tmp_data);
int		is_redirection(int token);
int		check_other_tokens(t_list **ptr, char *tmp_data);
int		precedence(int token);
int		ft_syntax_error(char *s);
int		is_white_space(char c);
int		is_word(int token);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:21:05 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/26 09:44:47 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "../minishell.h"

typedef struct s_list	t_list;
typedef struct s_tree	t_tree;

typedef struct s_tools
{
	int	is_wildcard;
	int	stars_num;
}				t_tools;

t_list	*tokenization(char *line, t_list *tokens);
t_list	*expand_tokens(t_list *tokens, t_list *new_tokens);
t_list	*filter(t_list *tokens, t_list *head);

void	expand_quotes(t_list **new_tokens, t_list **tokens, int token);
void	doubly_tokens(t_list **new_tokens, t_list **tokens, int token);
int		match_regex(char c);
int		match_regex_export(char c);
int		is_meta(char c);
int		is_and(char	*line);
void	free_list(t_list *tokens);
int		is_between_quotes(char *line, int index);
void	tokenize_wildcard(char *line, t_tools *tools, int *j);

#endif
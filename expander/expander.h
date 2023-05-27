/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:39:55 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/25 18:07:23 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../minishell.h"

typedef struct s_info	t_info;

typedef struct s_wildc
{
	char	*wildcard;
	char	*entity;
	int		exist;
	int		len_to_next;
	int		i;
	int		j;
}				t_wildc;

int		expander(t_tree *root, t_list *tokens, t_list *env);
int		exp_dollar(t_tree *root, t_list **tokens, t_list *env, t_list **head);
int		get_var(t_list **tokens, t_list *env, t_list **head);
int		split_var(t_list **head, t_list **tokens, char *tmp);
void	concate(t_list **tokens);
char	*getenv_var(t_list *env, char *str);
int		is_contain_char(char *str, char c);
void	free_splited(char **data);
int		expand_wildcard(t_tree *root, t_list *tokens);
t_list	*merge_lists(t_list *root_data, t_list **tokens, t_list *items);
void	expand_heredoc(char *file, t_list *env);
char	*search_and_expand(t_list *env, char *buff);
int		ambigious_redirect(t_list *tokens, t_list **items, int *i);
void	concate_with_previous(t_list *tokens, t_list **items);
t_list	*merge_with_next(t_list **tokens, t_list *items);
void	merge_with_prev(t_list **tokens, t_list *items);
void	merge_with_prev_and_next(t_list **tokens, t_list *items);
int		match_wildcard(char *wildcard, char *entity);
int		cases(t_wildc *data);
int		expand_wild_token(t_list *tokens, t_list **items, int *i);
void	initialize_wildc_data(t_wildc *data, char *wildcard, char *entity);
int		last_delimiter(char *str, int i);
int		next_delimiter(char *str, int i);
int		case_else(t_wildc *data);

#endif

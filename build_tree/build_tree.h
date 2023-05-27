/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:19:33 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/15 20:06:33 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILD_TREE_H
# define BUILD_TREE_H

# include "../minishell.h"

typedef struct s_list	t_list;
typedef struct s_info	t_info;

typedef struct s_tree
{
	int				token;
	t_list			*data;
	struct s_tree	*parent;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree;

t_tree	*build_tree(t_list *tokens);
t_tree	*ft_tree_add_new(t_list *data, int token);
void	ft_tree_add_left(t_tree **root, t_tree *new);
void	ft_tree_add_right(t_tree **root, t_tree *new);
void	ft_tree_add_root(t_tree **root, t_tree *new_root);

int		precedence(int token);
t_list	*new_list(t_list **tokens);

void	create_root(t_tree **root, t_list **tokens, t_list **elem_list);
int		expand_paren(t_tree **root, t_list **tokens, int i);
void	add_left_or_right(t_tree **root, t_list **tokens, t_list **elem_list);
void	swap_root(t_tree **root, t_list **tokens, t_list **elem_list);

#endif
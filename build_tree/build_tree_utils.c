/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:02:28 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/09 09:32:53 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build_tree.h"

int	expand_paren(t_tree **root, t_list **tokens, int i)
{
	t_tree	*new;
	t_list	*child_list;

	child_list = new_list(tokens);
	new = build_tree(child_list);
	free_list(child_list);
	if (i == 0)
	{
		*root = new;
		return (0);
	}
	else
		ft_tree_add_right(root, new);
	return (1);
}

void	create_root(t_tree **root, t_list **tokens, t_list **elem_list)
{
	if (precedence((*tokens)->token) == 0)
	{
		while ((*tokens) && precedence((*tokens)->token) == 0)
		{
			ft_lstadd_back(elem_list, \
			ft_lstnew((*tokens)->token, (*tokens)->data));
			(*tokens) = (*tokens)->next;
		}	
		*root = ft_tree_add_new(*elem_list, WORD);
	}
	else
	{
		ft_lstadd_back(elem_list, ft_lstnew((*tokens)->token, (*tokens)->data));
		ft_tree_add_root(root, ft_tree_add_new(*elem_list, (*tokens)->token));
		(*tokens) = (*tokens)->next;
	}
}

void	swap_root(t_tree **root, t_list **tokens, t_list **elem_list)
{
	while ((*root)->parent && precedence((*tokens)->token)
		>= precedence((*root)->parent->token))
		(*root) = (*root)->parent;
	ft_lstadd_back(elem_list, ft_lstnew((*tokens)->token, (*tokens)->data));
	ft_tree_add_root(root, ft_tree_add_new(*elem_list, (*tokens)->token));
	(*tokens) = (*tokens)->next;
}

void	add_left_or_right(t_tree **root, t_list **tokens, t_list **elem_list)
{
	int		tmp_token;

	tmp_token = (*tokens)->token;
	if (precedence((*tokens)->token) == 0)
	{
		while ((*tokens) && precedence((*tokens)->token) == 0)
		{
			ft_lstadd_back(elem_list, \
			ft_lstnew((*tokens)->token, (*tokens)->data));
			(*tokens) = (*tokens)->next;
		}
		tmp_token = WORD;
	}
	else
	{
		ft_lstadd_back(elem_list, ft_lstnew((*tokens)->token, (*tokens)->data));
		(*tokens) = (*tokens)->next;
	}
	if (!(*root)->left)
		ft_tree_add_left(root, ft_tree_add_new(*elem_list, tmp_token));
	else
		ft_tree_add_right(root, ft_tree_add_new(*elem_list, tmp_token));
}

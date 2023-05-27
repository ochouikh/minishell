/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:58:33 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/24 19:32:08 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build_tree.h"

int	precedence(int token)
{
	if (token <= D_LESS)
		return (0);
	if (token == PIPE)
		return (1);
	if (token == AND || token == OR)
		return (2);
	if (token == L_PAREN || token == R_PAREN)
		return (3);
	return (0);
}

t_list	*new_list(t_list **tokens)
{
	t_list	*new;
	int		last_paren;

	*tokens = (*tokens)->next;
	new = NULL;
	last_paren = 1;
	while (*tokens)
	{
		if ((*tokens)->token == L_PAREN)
			last_paren++;
		else if ((*tokens)->token == R_PAREN)
			last_paren--;
		if (last_paren == 0)
		{
			*tokens = (*tokens)->next;
			break ;
		}
		ft_lstadd_back(&new, ft_lstnew((*tokens)->token, (*tokens)->data));
		*tokens = (*tokens)->next;
	}
	return (new);
}

t_tree	*reset_root(t_tree *root)
{
	while (root->parent)
		root = root->parent;
	return (root);
}

t_tree	*build_tree(t_list *tokens)
{
	t_tree	*root;
	int		i;
	t_list	*new_list;

	if (!tokens)
		return (NULL);
	root = NULL;
	i = 0;
	while (tokens)
	{
		new_list = NULL;
		if (i == 0 && tokens->token != L_PAREN)
			create_root(&root, &tokens, &new_list);
		else if (tokens->token == L_PAREN)
		{
			if (!expand_paren(&root, &tokens, i))
				continue ;
		}
		else if (precedence(tokens->token) < precedence(root->token))
			add_left_or_right(&root, &tokens, &new_list);
		else if (precedence(tokens->token) >= precedence(root->token))
			swap_root(&root, &tokens, &new_list);
		i++;
	}
	return (reset_root(root));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_add_root.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:17:50 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/06 17:42:47 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build_tree.h"

void	ft_tree_add_root(t_tree **root, t_tree *new_root)
{
	t_tree	*tmp;

	tmp = *root;
	if (new_root)
	{
		new_root->parent = (*root)->parent;
		if (new_root->parent)
			new_root->parent->right = new_root;
		new_root->left = tmp;
		tmp->parent = new_root;
		*root = new_root;
	}
}

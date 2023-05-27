/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_add_right.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:11:39 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/06 17:42:39 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build_tree.h"

void	ft_tree_add_right(t_tree **root, t_tree *new)
{
	if (*root)
	{
		free((*root)->right);
		new->parent = *root;
		(*root)->right = new;
		*root = new;
	}
}

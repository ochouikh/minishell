/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_add_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:11:39 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/06 16:01:00 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build_tree.h"

void	ft_tree_add_left(t_tree **root, t_tree *new)
{
	if (*root)
	{
		free((*root)->left);
		new->parent = *root;
		(*root)->left = new;
		*root = new;
	}
}

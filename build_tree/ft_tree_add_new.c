/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_add_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:02:08 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/06 16:01:04 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "build_tree.h"

t_tree	*ft_tree_add_new(t_list *data, int token)
{
	t_tree	*root;

	root = malloc(sizeof(t_tree));
	if (!root)
		return (NULL);
	root->token = token;
	root->data = data;
	root->parent = NULL;
	root->left = NULL;
	root->right = NULL;
	return (root);
}

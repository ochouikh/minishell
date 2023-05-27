/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:24:37 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/10 18:49:11 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	concate_with_previous(t_list *tokens, t_list **items)
{
	char	*tmp;

	if (tokens->prev && tokens->prev->token == WORD && *items)
	{
		tmp = tokens->prev->data;
		tokens->prev->data = ft_strjoin(tokens->prev->data, (*items)->data);
		free(tmp);
		ft_lstdelnode(items);
	}
}

t_list	*merge_with_next(t_list **tokens, t_list *items)
{
	t_list	*head;

	ft_lstdelnode(tokens);
	head = items;
	while (items->next)
		items = items->next;
	items->next = *tokens;
	if ((*tokens))
		(*tokens)->prev = items;
	return (head);
}

void	merge_with_prev(t_list **tokens, t_list *items)
{
	ft_lstdelnode(tokens);
	(*tokens)->next = items;
	items->prev = (*tokens);
}

void	merge_with_prev_and_next(t_list **tokens, t_list *items)
{
	t_list	*tmp;

	ft_lstdelnode(tokens);
	(*tokens)->prev->next = items;
	items->prev = (*tokens)->prev;
	tmp = items;
	while (items->next)
		items = items->next;
	items->next = (*tokens);
	(*tokens)->prev = items;
	(*tokens) = tmp;
}

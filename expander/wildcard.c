/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:37:30 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/25 18:07:38 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_list	*merge_lists(t_list *root_data, t_list **tokens, t_list *items)
{
	t_list	*head;

	if (!items)
		return (root_data);
	if (!*tokens)
	{
		ft_lstdelnode(tokens);
		return (items);
	}
	else if (!(*tokens)->prev)
	{
		head = merge_with_next(tokens, items);
		return (head);
	}
	else if (!(*tokens)->next)
		merge_with_prev(tokens, items);
	else if ((*tokens)->prev && (*tokens)->next)
		merge_with_prev_and_next(tokens, items);
	return (root_data);
}

int	next_delimiter(char	*str, int index)
{
	int	i;

	i = 0;
	if (str[index + i] == '*')
	{
		i++;
		while (str[index + i])
		{
			if (str[index + i] == '*' && str[index + i - 1] != '*')
				break ;
			i++;
		}
	}
	else
	{
		while ((str[index + i] && str[index + i] != '*'))
			i++;
	}
	return (i);
}

int	last_delimiter(char *str, int index)
{
	int	i;

	i = 0;
	while (str[index + i])
	{
		if (str[index + i] == '*' && str[index + i - 1] != '*')
			return (0);
		i++;
	}
	return (i);
}

int	match_wildcard(char *wildcard, char *entity)
{
	t_wildc	data;

	initialize_wildc_data(&data, wildcard, entity);
	if (data.wildcard[0] != '.' && data.entity[0] == '.')
		return (0);
	while (data.wildcard[data.i] && data.entity[data.j])
	{
		if (data.wildcard[data.i] == '*' && data.wildcard[data.i - 1] != '*')
			data.i++;
		else
		{
			data.exist = 0;
			data.len_to_next = next_delimiter(data.wildcard, data.i);
			if (cases(&data) == 0)
				return (0);
			data.i += data.len_to_next;
			data.j += data.len_to_next;
		}
		if (((data.wildcard[data.i] && data.wildcard[data.i] != '*')
				|| (data.wildcard[data.i] == '*' && data.wildcard[data.i + 1]))
			&& data.entity[data.j] == '\0')
			return (0);
	}
	return (1);
}

int	expand_wildcard(t_tree *root, t_list *tokens)
{
	t_list			*items;
	int				i;

	while (tokens)
	{
		i = 0;
		if (tokens->token == WILDCARD)
		{
			items = NULL;
			if (expand_wild_token(tokens, &items, &i) != 0)
				return (i);
			concate_with_previous(tokens, &items);
			tokens->token = WORD;
			root->data = merge_lists(root->data, &tokens, items);
		}
		if (tokens)
			tokens = tokens->next;
	}
	return (0);
}

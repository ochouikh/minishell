/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 08:33:22 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/24 19:42:02 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	free_list(t_list *tokens)
{
	t_list	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		ft_lstdelone(tmp);
	}
}

void	tokenize_wildcard(char *line, t_tools *tools, int *j)
{
	tools->is_wildcard = 1;
	tools->stars_num = -1;
	while (line[*j] == '*')
	{
		tools->stars_num++;
		(*j)++;
	}
}

int	is_between_quotes(char *line, int index)
{
	int		i;
	int		before;
	char	elem;

	before = 0;
	i = 0;
	while (i < index)
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			elem = line[i];
			while (line[i] && i < index && line[i] != elem)
				i++;
			if (line[i] != elem)
				before = 1;
			i++;
		}
		else
			i++;
	}
	if (before)
		return (1);
	return (0);
}

t_list	*expand_tokens(t_list *tokens, t_list *new_tokens)
{
	t_list	*tmp;

	tmp = tokens;
	while (tokens)
	{
		if (tokens->token == SP)
		{
			ft_lstadd_back(&new_tokens, ft_lstnew(tokens->token, tokens->data));
			tokens = tokens->next;
			while (tokens && tokens->token == SP)
				tokens = tokens->next;
		}
		else if (tokens->token == QUOTE || tokens->token == D_QUOTE)
			expand_quotes(&new_tokens, &tokens, tokens->token);
		else if (tokens->token == LESS || tokens->token == GREAT
			|| tokens->token == PIPE)
			doubly_tokens(&new_tokens, &tokens, tokens->token);
		else
		{
			ft_lstadd_back(&new_tokens, ft_lstnew(tokens->token, tokens->data));
			tokens = tokens->next;
		}
	}
	free_list(tmp);
	return (filter(new_tokens, NULL));
}

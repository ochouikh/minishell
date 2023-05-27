/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:20:35 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/04 16:55:48 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	is_and(char	*line)
{
	int	i;

	i = 0;
	if (line && line[i] == '&' && line[i + 1] && line[i + 1] == '&')
		return (1);
	return (0);
}

int	match_regex(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	else if (c >= '0' && c <= '9')
		return (2);
	return (0);
}

int	match_regex_export(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| c == '_' || c == '$')
		return (1);
	else if (c >= '0' && c <= '9')
		return (2);
	return (0);
}

int	is_meta(char c)
{
	if (c == '|' || c == '\'' || c == '\"' || c == '>'
		|| c == '<' || c == '(' || c == ')')
		return (1);
	return (0);
}

t_list	*filter(t_list *tokens, t_list *head)
{
	head = tokens;
	while (tokens)
	{
		if (tokens->token == SP)
		{
			if (!tokens->next || !tokens->prev)
			{
				ft_lstdelnode(&tokens);
				if (!tokens || !tokens->prev)
					head = tokens;
			}
			else if (!is_word(tokens->prev->token)
				|| !is_word(tokens->next->token))
			{
				ft_lstdelnode(&tokens);
				if (!tokens || !tokens->prev)
					head = tokens;
			}
			else
				tokens = tokens->next;
		}
		else
			tokens = tokens->next;
	}
	return (head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 08:46:41 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/04 10:27:42 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	doubly_tokens(t_list **new_tokens, t_list **tokens, int token)
{
	char	*data;
	int		new_token;

	if ((*tokens)->next && (*tokens)->next->token == token)
	{
		new_token = D_LESS;
		data = "<<";
		if (token == GREAT)
		{
			new_token = D_GREAT;
			data = ">>";
		}
		else if (token == PIPE)
		{
			new_token = OR;
			data = "||";
		}
		ft_lstadd_back(new_tokens, ft_lstnew(new_token, data));
		(*tokens) = (*tokens)->next;
	}
	else
		ft_lstadd_back(new_tokens, ft_lstnew(token, (*tokens)->data));
	(*tokens) = (*tokens)->next;
}

char	*join(t_list **new_tokens, t_list **tokens, int token, char *joined)
{
	char	*tmp;

	while ((*tokens) && (*tokens)->token != token)
	{
		if (token == D_QUOTE && (*tokens)->token == DOLLAR)
		{
			(*tokens)->token = Q_DOLLAR;
			if (joined)
			{
				ft_lstadd_back(new_tokens, ft_lstnew(WORD, joined));
				free(joined);
				joined = NULL;
			}
			ft_lstadd_back(new_tokens, ft_lstnew(Q_DOLLAR, (*tokens)->data));
		}
		else
		{
			tmp = joined;
			joined = ft_strjoin(joined, (*tokens)->data);
			free(tmp);
		}
		(*tokens) = (*tokens)->next;
	}
	return (joined);
}

void	expand_quotes(t_list **new_tokens, t_list **tokens, int token)
{
	char	*joined;

	ft_lstadd_back(new_tokens, ft_lstnew(token, (*tokens)->data));
	(*tokens) = (*tokens)->next;
	joined = join(new_tokens, tokens, token, NULL);
	if (joined)
	{
		ft_lstadd_back(new_tokens, ft_lstnew(WORD, joined));
		free(joined);
	}
	if ((*tokens) && (*tokens)->token == token)
	{
		ft_lstadd_back(new_tokens, ft_lstnew(token, (*tokens)->data));
		(*tokens) = (*tokens)->next;
	}
}

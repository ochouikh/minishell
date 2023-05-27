/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:01:01 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/24 17:51:46 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	empty_token(t_list **ptr)
{
	(*ptr)->token = QUOTES;
	free((*ptr)->data);
	(*ptr)->data = ft_strdup("");
}

int	is_redirection(int token)
{
	if (token == LESS || token == GREAT || token == D_LESS || token == D_GREAT)
		return (1);
	return (0);
}

int	check_quotes(t_list **ptr, char *tmp_data, t_list **head)
{
	int		elem;

	elem = (*ptr)->token;
	ft_lstdelnode(ptr);
	if (!(*ptr) || (*ptr && !(*ptr)->prev))
		*head = (*ptr);
	if ((*ptr) && (*ptr)->token == elem)
		empty_token(ptr);
	else
	{
		while ((*ptr) && (*ptr)->token != elem)
		{
			if ((*ptr)->token != DOLLAR && (*ptr)->token != Q_DOLLAR)
				(*ptr)->token = QUOTES;
			(*ptr) = (*ptr)->next;
		}
		if (!(*ptr) || (*ptr)->token != elem)
			return (ft_syntax_error(tmp_data));
		ft_lstdelnode(ptr);
		if (!(*ptr) || !(*ptr)->prev)
			*head = (*ptr);
	}
	return (0);
}

int	check_redirections(t_list **ptr, char *tmp_data)
{
	if ((*ptr)->prev && (*ptr)->prev->token == R_PAREN)
		return (ft_syntax_error(tmp_data));
	(*ptr) = (*ptr)->next;
	if (!(*ptr) || !is_word((*ptr)->token))
		return (ft_syntax_error(tmp_data));
	return (0);
}

int	check_other_tokens(t_list **ptr, char *tmp_data)
{
	t_list	*tmp;

	tmp = (*ptr)->prev;
	if (!tmp || tmp->token == PIPE || tmp->token == OR
		|| tmp->token == AND || tmp->token == L_PAREN)
	{
		return (ft_syntax_error(tmp_data));
	}
	(*ptr) = (*ptr)->next;
	if (!(*ptr) || (*ptr)->token == R_PAREN)
	{
		return (ft_syntax_error(tmp_data));
	}
	return (0);
}

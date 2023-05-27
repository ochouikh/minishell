/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:29:44 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/24 18:11:38 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*check_parentheses(t_list *tokens, t_info *infos)
{
	while (tokens && tokens->token != L_PAREN && tokens->token != R_PAREN)
		tokens = tokens->next;
	if (tokens && tokens->token == R_PAREN)
	{
		infos->opened_paren--;
		return (check_parentheses(tokens->next, infos));
	}
	else if (tokens && tokens->token == L_PAREN)
	{
		infos->opened_paren++;
		return (check_parentheses(tokens->next, infos));
	}
	return (NULL);
}

int	check_unchecked_paren(t_list *ptr, t_info *infos, char *tmp_data)
{
	infos->opened_paren = 1;
	check_parentheses(ptr->next, infos);
	if (infos->opened_paren != 0)
	{
		return (ft_syntax_error(tmp_data));
	}
	return (0);
}

int	surrounded_by_parens(t_list *ptr)
{
	if (ptr->prev && ptr->prev->token == L_PAREN)
	{
		while (ptr && ptr->token != R_PAREN)
			ptr = ptr->next;
		ptr = ptr->next;
		if (ptr && ptr->token == R_PAREN)
			return (1);
	}
	return (0);
}

int	check_checked_paren(t_list **ptr, char *tmp_data)
{
	if ((*ptr)->next && (*ptr)->next->token == R_PAREN)
	{
		return (ft_syntax_error(tmp_data));
	}
	if ((*ptr)->prev && precedence((*ptr)->prev->token) == 0)
	{
		return (ft_syntax_error(tmp_data));
	}
	if (surrounded_by_parens(*ptr))
	{
		return (ft_syntax_error(tmp_data));
	}
	(*ptr) = (*ptr)->next;
	return (0);
}

int	check_parens(t_list **ptr, int *checked, t_info *infos, char *tmp_data)
{
	int	status;

	status = 0;
	if ((*ptr)->token == R_PAREN && !*checked)
		return (ft_syntax_error(tmp_data));
	else if ((*ptr)->token == R_PAREN && checked)
	{
		if ((*ptr)->next && (*ptr)->next->token != PIPE
			&& (*ptr)->next->token != AND && (*ptr)->next->token != OR
			&& (*ptr)->next->token != R_PAREN)
			return (ft_syntax_error((*ptr)->next->data));
		*ptr = (*ptr)->next;
	}
	else if ((*ptr)->token == L_PAREN)
	{
		if (!*checked)
			status = check_unchecked_paren((*ptr), infos, tmp_data);
		else
			status = check_checked_paren(ptr, tmp_data);
		*checked = 1;
	}
	return (status);
}

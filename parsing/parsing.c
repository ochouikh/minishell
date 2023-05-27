/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:13:06 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/18 15:48:41 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static void	ft_free(t_list *lst)
{
	free(lst->data);
	lst->data = NULL;
	free(lst);
	lst = NULL;
}

int	is_word(int token)
{
	if (token == WORD || token == QUOTE || token == D_QUOTE
		|| token == DOLLAR || token == WILDCARD)
		return (1);
	return (0);
}

void	ft_lstdelnode(t_list **list)
{
	t_list	*tmp;

	if (*list != NULL)
	{
		tmp = *list;
		if ((*list)->prev && (*list)->next)
		{
			(*list)->prev->next = (*list)->next;
			(*list)->next->prev = (*list)->prev;
			*list = (*list)->next;
		}
		else if (!(*list)->prev && (*list)->next)
		{
			*list = (*list)->next;
			(*list)->prev = NULL;
		}
		else if ((*list)->prev && !(*list)->next)
		{
			*list = (*list)->prev;
			(*list)->next = NULL;
		}
		else if (!(*list)->prev && !(*list)->next)
			*list = NULL;
		ft_free(tmp);
	}
}

int	parsing(t_list **tokens, t_info *infos, int status)
{
	char	*tmp_data;
	int		checked;
	t_list	*ptr;

	ptr = *tokens;
	checked = 0;
	while (ptr && !status)
	{
		tmp_data = ft_strdup(ptr->data);
		if (ptr->token == QUOTE || ptr->token == D_QUOTE)
			status = check_quotes(&ptr, tmp_data, tokens);
		else if (is_redirection(ptr->token))
			status = check_redirections(&ptr, tmp_data);
		else if (ptr->token == PIPE || ptr->token == OR || ptr->token == AND)
			status = check_other_tokens(&ptr, tmp_data);
		else if (ptr->token == L_PAREN || ptr->token == R_PAREN)
			status = check_parens(&ptr, &checked, infos, tmp_data);
		else
			ptr = ptr->next;
		free(tmp_data);
	}
	return (status);
}

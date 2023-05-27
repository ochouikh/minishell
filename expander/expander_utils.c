/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:25:46 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/25 17:00:29 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	after_redirect(t_list *tokens)
{
	while (tokens)
	{
		if (tokens->token == LESS || tokens->token == GREAT
			|| tokens->token == D_GREAT)
			return (1);
		tokens = tokens->prev;
	}
	return (0);
}

int	is_alone(t_list *tokens)
{
	if (!tokens->prev || tokens->prev->token == SP)
		return (1);
	return (0);
}

int	get_var(t_list **tokens, t_list *env, t_list **head)
{
	if ((*tokens)->token == Q_DOLLAR)
		(*tokens)->token = QUOTES;
	else
		(*tokens)->token = WORD;
	if (*((*tokens)->data + 1) == '?')
		(*tokens)->data = ft_itoa(g_exit_status);
	else
		(*tokens)->data = getenv_var(env, (*tokens)->data + 1);
	if (!(*tokens)->data)
	{
		ft_lstdelnode(tokens);
		if (*tokens && (*tokens)->token == SP
			&& is_alone(*tokens) && !after_redirect(*tokens))
			ft_lstdelnode(tokens);
		if (!(*tokens) || !(*tokens)->prev)
			*head = (*tokens);
		return (0);
	}
	return (1);
}

int	split_var(t_list **head, t_list **tokens, char *tmp)
{
	char	**splited_var;
	int		i;
	t_list	*new;

	if ((*tokens)->prev && ((*tokens)->prev->token == LESS
			|| (*tokens)->prev->token == GREAT
			|| (*tokens)->prev->token == D_GREAT))
	{
		printf("minishell: %s: ambiguous redirect\n", tmp);
		free(tmp);
		g_exit_status = 1;
		return (0);
	}
	splited_var = ft_split((*tokens)->data, ' ');
	i = -1;
	new = NULL;
	while (splited_var[++i])
	{
		ft_lstadd_back(&new, ft_lstnew(WORD, splited_var[i]));
		if (splited_var[i + 1])
			ft_lstadd_back(&new, ft_lstnew(SP, " "));
	}
	free_splited(splited_var);
	*head = merge_lists(*head, tokens, new);
	return (1);
}

void	concate(t_list **tokens)
{
	t_list	*tmp;
	char	*data_tmp;
	t_list	*ptr;

	ptr = *tokens;
	if (!ptr)
		return ;
	if (ptr && (ptr->token == WORD || ptr->token == WILDCARD)
		&& ptr->prev && (ptr->prev->token == WORD
			|| ptr->prev->token == WILDCARD))
	{
		(*tokens) = (*tokens)->prev;
		ptr = *tokens;
		data_tmp = ptr->data;
		tmp = ptr->next;
		if (ptr->token == WILDCARD || tmp->token == WILDCARD)
			ptr->token = WILDCARD;
		ptr->data = ft_strjoin(ptr->data, tmp->data);
		free(data_tmp);
		ft_lstdelnode(&tmp);
	}
}

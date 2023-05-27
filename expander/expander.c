/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:36:10 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/25 16:53:20 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*getenv_var(t_list *env, char *str)
{
	char	*tmp;

	while (env)
	{
		tmp = ft_strjoin(str, "=");
		if (ft_strncmp(tmp, env->data, ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (ft_strdup(ft_strchr(env->data, '=') + 1));
		}
		free(tmp);
		env = env->next;
	}
	return (NULL);
}

int	is_contain_char(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	free_splited(char **data)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	free(data);
}

int	exp_dollar(t_tree *root, t_list **tokens, t_list *env, t_list **head)
{
	char	*tmp;

	tmp = (*tokens)->data;
	if (get_var(tokens, env, head))
	{
		if ((*tokens) && (*tokens)->token == WORD
			&& is_contain_char((*tokens)->data, ' '))
		{
			if (!split_var(head, tokens, tmp))
				return (0);
		}
		if (*tokens && (*tokens)->token == QUOTES)
			(*tokens)->token = WORD;
	}
	root->data = (*head);
	free(tmp);
	tmp = NULL;
	return (1);
}

int	expander(t_tree *root, t_list *tokens, t_list *env)
{
	int		is_wildcard;
	t_list	*head;

	is_wildcard = 0;
	head = tokens;
	while (tokens)
	{
		if (tokens->token == DOLLAR || tokens->token == Q_DOLLAR)
		{
			if (exp_dollar(root, &tokens, env, &head) == 0)
				return (0);
		}
		concate(&tokens);
		if (tokens && tokens->token == WILDCARD)
			is_wildcard = 1;
		if (tokens && tokens->token != DOLLAR && tokens->token != Q_DOLLAR)
			tokens = tokens->next;
	}
	if (is_wildcard)
		if (expand_wildcard(root, head) > 1)
			return (0);
	return (1);
}

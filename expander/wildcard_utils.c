/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:04:15 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/25 17:56:42 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	expand_wild_token(t_list *tokens, t_list **items, int *i)
{
	DIR				*dir;
	struct dirent	*entity;

	dir = opendir(".");
	entity = readdir(dir);
	while (entity)
	{
		if (match_wildcard(tokens->data, entity->d_name))
		{
			ft_lstadd_back(items, ft_lstnew(WORD, entity->d_name));
			ft_lstadd_back(items, ft_lstnew(SP, " "));
			(*i)++;
			if (ambigious_redirect(tokens, items, i))
			{
				closedir(dir);
				return (*i);
			}
		}
		entity = readdir(dir);
	}
	closedir(dir);
	return (0);
}

void	initialize_wildc_data(t_wildc *data, char *wildcard, char *entity)
{
	data->i = 0;
	data->j = 0;
	data->wildcard = wildcard;
	data->entity = entity;
}

int	cases(t_wildc *data)
{
	if (data->i == 0)
	{
		if (ft_strncmp(data->wildcard + data->i, data->entity \
			+ data->j, data->len_to_next) != 0)
			return (0);
	}
	else if (last_delimiter(data->wildcard, data->i))
	{
		if (ft_strncmp(data->wildcard + data->i, data->entity \
			+ ft_strlen(data->entity) - ft_strlen(data->wildcard + data->i), \
			data->len_to_next) != 0)
			return (0);
	}
	else
	{
		if (case_else(data) == 0)
			return (0);
	}
	return (1);
}

int	case_else(t_wildc *data)
{
	while (data->entity[data->j])
	{
		if (ft_strncmp(data->wildcard + data->i, \
		data->entity + data->j, data->len_to_next) == 0)
		{
			data->exist = 1;
			break ;
		}
		data->j++;
	}
	if (!data->exist)
		return (0);
	return (1);
}

int	ambigious_redirect(t_list *tokens, t_list **items, int *i)
{
	if (*i > 1 && tokens->prev && (tokens->prev->token == LESS
			|| tokens->prev->token == GREAT || tokens->prev->token == D_GREAT))
	{
		printf("minishell: %s: ambiguous redirect\n", tokens->data);
		free_list(*items);
		g_exit_status = 1;
		return (*i);
	}
	return (0);
}

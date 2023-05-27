/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:35:40 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/25 15:49:53 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	case_less_dless(t_list *tmp, t_list *env)
{
	int	open_file;

	if (tmp->token == LESS)
	{
		open_file = open(tmp->next->data, O_RDONLY);
		if (open_file == -1)
			return (perror("minishell"), 1);
	}
	else
	{
		expand_heredoc(tmp->next->data, env);
		open_file = open(tmp->next->data, O_RDONLY);
		if (open_file == -1)
			return (perror("minishell"), 1);
	}
	if (dup2(open_file, 0) == -1)
	{
		perror("dup2()");
		exit(EXIT_FAILURE);
	}
	close(open_file);
	return (0);
}

static int	case_great_dgreat(t_list *tmp)
{
	int	open_file;

	if (tmp->token == GREAT)
	{
		open_file = open(tmp->next->data, O_CREAT | O_WRONLY | \
		O_TRUNC, 0644);
		if (open_file == -1)
			return (perror("minishell"), 1);
	}
	else
	{
		open_file = open(tmp->next->data, O_CREAT | O_WRONLY | \
		O_APPEND, 0644);
		if (open_file == -1)
			return (perror("minishell"), 1);
	}
	if (dup2(open_file, 1) == -1)
	{
		perror("dup2()");
		exit(EXIT_FAILURE);
	}
	close(open_file);
	return (0);
}

static int	open_file_and_redirect(t_list *tmp, t_list *env)
{
	if ((tmp->token == LESS) || (tmp->token == D_LESS))
	{
		if (case_less_dless(tmp, env))
			return (1);
	}
	else if ((tmp->token == GREAT) || (tmp->token == D_GREAT))
	{
		if (case_great_dgreat(tmp))
			return (1);
	}
	return (0);
}

int	ambigious(t_list *tmp)
{
	if (tmp->token != D_LESS && (!tmp->next || tmp->next->token != WORD))
	{
		printf("minishell: ambiguous redirect\n");
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

int	redirections(t_tree *root, t_list *env)
{
	t_list	*tmp;
	t_list	*head;

	tmp = root->data;
	head = tmp;
	while (tmp)
	{
		if ((tmp->token == LESS) || (tmp->token == GREAT)
			|| (tmp->token == D_GREAT) || (tmp->token == D_LESS))
		{
			if (ambigious(tmp) || open_file_and_redirect(tmp, env))
				return (1);
			ft_lstdelnode(&tmp);
			ft_lstdelnode(&tmp);
			head = tmp;
		}
		else
			tmp = tmp->next;
	}
	root->data = head;
	while (root->data->prev)
		root->data = (root->data)->prev;
	return (0);
}

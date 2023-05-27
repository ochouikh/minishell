/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:01:57 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/24 18:27:05 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

char	*find_correct_file(int quote)
{
	char	*name;
	char	*num;
	char	*tmp;
	int		i;

	tmp = ft_strdup(".tmp");
	if (quote)
	{
		free(tmp);
		tmp = ft_strdup(".qtmp");
	}
	i = 0;
	num = ft_itoa(i);
	name = ft_strjoin(tmp, num);
	while (access(name, F_OK) == 0)
	{
		i++;
		free(name);
		free(num);
		num = ft_itoa(i);
		name = ft_strjoin(tmp, num);
	}
	free(tmp);
	free(num);
	return (name);
}

void	open_heredoc_file(t_list *lst, int quote, t_list **heredoc_files)
{
	char	*name;

	name = find_correct_file(quote);
	open_tmp_file(name, lst->next->data);
	free(lst->next->data);
	lst->next->data = ft_strdup(name);
	ft_lstadd_back(heredoc_files, ft_lstnew(WORD, name));
	free(name);
}

void	concate_and_open(t_list **tokens, t_list **heredoc_files, t_list *tmp2)
{
	t_list	*tmp;
	char	*old_data;
	int		is_quote_exist;

	tmp = (*tokens)->next;
	is_quote_exist = 0;
	if ((*tokens)->token == QUOTES)
		is_quote_exist = 1;
	while (tmp && (tmp->token == WORD
			|| tmp->token == DOLLAR || tmp->token == QUOTES
			|| tmp->token == Q_DOLLAR))
	{
		if (tmp->token == QUOTES)
			is_quote_exist = 1;
		old_data = (*tokens)->data;
		(*tokens)->data = ft_strjoin((*tokens)->data, tmp->data);
		free(old_data);
		ft_lstdelnode(&tmp);
		tmp = (*tokens)->next;
	}
	(*tokens)->token = WORD;
	open_heredoc_file(tmp2, is_quote_exist, heredoc_files);
}

void	search_heredoc(t_list *tokens, t_list **heredoc_files)
{
	t_list	*d_less;

	while (tokens)
	{
		if (tokens->token == D_LESS)
		{
			d_less = tokens;
			tokens = tokens->next;
			concate_and_open(&tokens, heredoc_files, d_less);
		}
		else
		{
			if (tokens->token == QUOTES)
				tokens->token = WORD;
			tokens = tokens->next;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:13:07 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/24 18:44:15 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	tokenize_dollar(t_list **tokens, char *line, int i, char c)
{
	char	*tmp;
	int		j;

	if (c == '?')
	{
		ft_lstadd_back(tokens, ft_lstnew(DOLLAR, "$?"));
		return (1);
	}
	j = 0;
	while (line[i + j] && match_regex(line[i + j]))
		j++;
	tmp = ft_substr(line, i - 1, j + 1);
	ft_lstadd_back(tokens, ft_lstnew(DOLLAR, tmp));
	free(tmp);
	return (j);
}

void	add_elem(t_list **tokens, char *line, int j, t_tools *tools)
{
	char	*tmp;

	tmp = ft_substr(line, 0, j - tools->stars_num);
	if (tools->is_wildcard)
		ft_lstadd_back(tokens, ft_lstnew(WILDCARD, tmp));
	else
		ft_lstadd_back(tokens, ft_lstnew(WORD, tmp));
	free(tmp);
}

int	tokenize_word(t_list **tokens, char *line, int i)
{
	t_tools	tools;
	int		j;

	tools.is_wildcard = 0;
	tools.stars_num = 0;
	j = 0;
	while (line[i + j] && !is_white_space(line[i + j]) && !is_meta(line[i + j])
		&& !is_and(line + i + j))
	{
		if (line[i + j] == '$' && line[i + j + 1]
			&& (line[i + j + 1] == '?' || match_regex(line[i + j + 1]) == 1))
			break ;
		if (line[i + j] == '*')
		{
			if (!is_between_quotes(line, i + j))
			{
				tokenize_wildcard(line + i, &tools, &j);
				break ;
			}
		}
		j++;
	}
	add_elem(tokens, line + i, j, &tools);
	return (j);
}

void	tokenize_meta_chars(t_list **tokens, char c)
{
	if (is_white_space(c))
		ft_lstadd_back(tokens, ft_lstnew(SP, " "));
	else if (c == '|')
		ft_lstadd_back(tokens, ft_lstnew(PIPE, "|"));
	else if (c == '\'')
		ft_lstadd_back(tokens, ft_lstnew(QUOTE, "'"));
	else if (c == '"')
		ft_lstadd_back(tokens, ft_lstnew(D_QUOTE, "\""));
	else if (c == '>')
		ft_lstadd_back(tokens, ft_lstnew(GREAT, ">"));
	else if (c == '<')
		ft_lstadd_back(tokens, ft_lstnew(LESS, "<"));
	else if (c == '(')
		ft_lstadd_back(tokens, ft_lstnew(L_PAREN, "("));
	else if (c == ')')
		ft_lstadd_back(tokens, ft_lstnew(R_PAREN, ")"));
}

t_list	*tokenization(char *line, t_list *tokens)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (is_meta(line[i]) || is_white_space(line[i]))
			tokenize_meta_chars(&tokens, line[i]);
		else if (line[i] == '&' && line[i + 1] && line[i + 1] == '&')
		{
			ft_lstadd_back(&tokens, ft_lstnew(AND, "&&"));
			i++;
		}
		else if (line[i] == '$' && line[i + 1] && match_regex(line[i + 1]) == 1)
		{
			i++;
			i += tokenize_dollar(&tokens, line, i, 'w') - 1;
		}
		else if (line[i] == '$' && line[i + 1] && line[i + 1] == '?')
			i += tokenize_dollar(&tokens, line, i, '?');
		else
			i += tokenize_word(&tokens, line, i) - 1;
		i++;
	}
	return (expand_tokens(tokens, NULL));
}

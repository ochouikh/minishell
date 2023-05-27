/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:02:23 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/12 12:17:00 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*continue_expanding(t_list *env, char *buff, char *tmp, int l)
{
	char	*str;
	char	*s;
	char	*t;

	if (env)
	{
		s = ft_strchr(env->data, '=') + 1;
		s = ft_strjoin(tmp, s);
		t = ft_substr(buff, l, ft_strlen(buff));
		str = ft_strjoin(s, t);
		free(t);
	}
	else
	{
		s = ft_substr(buff, l, ft_strlen(buff));
		str = ft_strjoin(tmp, s);
	}
	free(s);
	return (str);
}

static char	*expand_var(t_list *env, char *buff, char *tmp, int *k)
{
	char	*str;
	char	*s;
	char	*t;
	int		l;
	int		m;

	l = *k;
	m = 0;
	while (buff[++l] && match_regex(buff[l]) != 0)
		m++;
	s = ft_substr(buff, *k + 1, m);
	t = s;
	s = ft_strjoin(s, "=");
	free(t);
	while (env && ft_strncmp(s, env->data, ft_strlen(s)) != 0)
		env = env->next;
	str = continue_expanding(env, buff, tmp, l);
	free(s);
	*k = l;
	return (str);
}

char	*search_and_expand(t_list *env, char *buff)
{
	char	*str;
	char	*tmp;
	char	*t;
	int		k;

	str = ft_strdup(buff);
	k = 0;
	while (str[k])
	{
		if (str[k] == '$' && str[k + 1] && match_regex(str[k + 1]) == 1)
		{
			tmp = ft_substr(str, 0, k);
			t = str;
			str = expand_var(env, str, tmp, &k);
			free(t);
		}
		else
			k++;
	}
	return (str);
}

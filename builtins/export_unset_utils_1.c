/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_utils_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:45:41 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/09 15:47:37 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_list	*ft_search_for_var(t_list **envp, char *tab, char *str, int i)
{
	t_list	*tmp;
	char	*var;

	tmp = *envp;
	while (tmp && ft_strncmp(str, (tmp)->data, ft_strlen(str)) != 0)
		tmp = (tmp)->next;
	if (!tmp)
	{
		var = ft_substr(tab, 0, i);
		tmp = *envp;
		while (tmp)
		{
			if (!ft_strchr(tmp->data, '=') && ft_strncmp(var, (tmp)->data,
					ft_max(ft_strlen(tmp->data), ft_strlen(var))) == 0)
				break ;
			tmp = tmp->next;
		}
		free(var);
	}
	return (tmp);
}

void	ft_replace_eq(t_list **envp, t_list *tmp, char *tab)
{
	if (!tmp)
		ft_lstadd_back(envp, ft_lstnew(ENV, tab));
	else
	{
		free(tmp->data);
		tmp->data = ft_strdup(tab);
	}
}

static char	*find_var(char *tab, int i)
{
	char	*str;
	char	*t;

	str = ft_substr(tab, 0, i);
	t = str;
	str = ft_strjoin(str, "=");
	free(t);
	return (str);
}

void	ft_replace_add(t_list **envp, t_list *tmp, char *tab, int i)
{
	char	*str;
	char	*t;
	char	*content;

	str = find_var(tab, i);
	content = ft_substr(tab, i + 2, ft_strlen(tab));
	if (!tmp)
	{
		t = ft_strjoin(str, content);
		ft_lstadd_back(envp, ft_lstnew(ENV, t));
	}
	else
	{
		if (!ft_strchr(tmp->data, '='))
		{
			free(tmp->data);
			tmp->data = ft_strdup(str);
		}
		t = tmp->data;
		tmp->data = ft_strjoin(tmp->data, content);
	}
	free(t);
	free(str);
	free(content);
}

int	valid_var(char *s, char c, int type)
{
	int		i;
	char	*cmd;

	cmd = "unset";
	if (type == 2)
		cmd = "export";
	if ((!s[0]) || (s[0] && !ft_isalpha(s[0]) && s[0] != '_'))
	{
		ft_printf(2, "minishell: %s: `%s': not a valid identifier\n", cmd, s);
		return (0);
	}
	else if (s[0] && c == 'u')
	{
		i = 0;
		while (s[++i])
		{
			if (!ft_isalnum(s[i]) && s[i] != '_')
			{
				ft_printf(2, "minishell: %s: `%s': not a valid identifier\n", \
				cmd, s);
				return (0);
			}
		}
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:41:23 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/25 16:46:39 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	case_no_assign(t_list **export, char *tab)
{
	char	*str;
	t_list	*tmp;

	tmp = *export;
	str = ft_strjoin(tab, "=");
	while (tmp && ft_strncmp(str, (tmp)->data, ft_strlen(str)) != 0)
		tmp = (tmp)->next;
	if (!tmp)
	{
		tmp = *export;
		while (tmp)
		{
			if (!ft_strchr(tmp->data, '=')
				&& ft_strncmp(tab, (tmp)->data, ft_strlen(tab)) == 0)
				break ;
			tmp = tmp->next;
		}
		if (!tmp)
			ft_lstadd_back(export, ft_lstnew(ENV, tab));
	}
	free(str);
}

static void	case_eq(t_list **envp, t_list **export, char *tab, int i)
{
	char	*str;
	t_list	*tmp;
	t_list	*new_export;

	str = ft_substr(tab, 0, i + 1);
	tmp = ft_search_for_var(envp, tab, str, i);
	new_export = ft_search_for_var(export, tab, str, i);
	ft_replace_eq(envp, tmp, tab);
	ft_replace_eq(export, new_export, tab);
	free(str);
}

static void	case_add(t_list **envp, t_list **export, char *tab, int i)
{
	char	*str;
	char	*t;
	t_list	*tmp;
	t_list	*new_export;

	str = ft_substr(tab, 0, i);
	t = str;
	str = ft_strjoin(str, "=");
	free(t);
	tmp = ft_search_for_var(envp, tab, str, i);
	new_export = ft_search_for_var(export, tab, str, i);
	ft_replace_add(envp, tmp, tab, i);
	ft_replace_add(export, new_export, tab, i);
	free(str);
}

int	apply_export(t_list **envp, t_list **export, char *s)
{
	int	i;

	i = 0;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	if (s[i] == '=')
		case_eq(envp, export, s, i);
	else if (s[i] == '+' && s[i + 1] && s[i + 1] == '=')
		case_add(envp, export, s, i);
	else if ((s[i] && s[i] == '+' && s[i + 1] && s[i + 1] != '=')
		|| (s[i] && !ft_isalnum(s[i]) && s[i] != '_' && s[i] != '='))
	{
		ft_printf(2, "minishell: export: `%s': not a valid identifier\n", s);
		return (0);
	}
	else
		case_no_assign(export, s);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:32:47 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/18 18:07:16 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_list	*ft_searsh(t_list **export, char *tab)
{
	t_list	*new_export;

	new_export = *export;
	while (new_export)
	{
		if (!ft_strchr(new_export->data, '=')
			&& ft_strncmp(tab, (new_export)->data,
				ft_max(ft_strlen(new_export->data), ft_strlen(tab))) == 0)
			break ;
		new_export = new_export->next;
	}
	return (new_export);
}

static t_list	*ft_searsh_var(t_list **envp, char *tab)
{
	t_list	*tmp;
	char	*str;

	str = ft_strjoin(tab, "=");
	tmp = (*envp);
	while (tmp && ft_strncmp(str, (tmp)->data, ft_strlen(str)) != 0)
		(tmp) = (tmp)->next;
	free(str);
	return (tmp);
}

void	fix_lst(t_list **env, t_list *tmp)
{
	if (!tmp || !tmp->prev)
		*env = tmp;
}

static void	search_and_free(t_list **envp, t_list **export, char *tab)
{
	t_list	*tmp;
	t_list	*new_export;

	tmp = ft_searsh_var(envp, tab);
	new_export = ft_searsh_var(export, tab);
	if (tmp)
	{
		ft_lstdelnode(&tmp);
		fix_lst(envp, tmp);
	}
	if (new_export)
	{
		ft_lstdelnode(&new_export);
		fix_lst(export, new_export);
	}
	else if (!new_export)
	{
		new_export = ft_searsh(export, tab);
		if (new_export)
		{
			ft_lstdelnode(&new_export);
			fix_lst(export, new_export);
		}
	}
}

int	ft_unset(t_list *cmd_line, t_list **envp, t_list **export)
{
	int	n;

	n = 0;
	cmd_line = cmd_line->next;
	while (cmd_line)
	{
		if (cmd_line->token == WORD)
		{
			if (valid_var(cmd_line->data, 'u', 1))
				search_and_free(envp, export, cmd_line->data);
			else
				n = 1;
		}
		cmd_line = cmd_line->next;
	}
	return (n);
}

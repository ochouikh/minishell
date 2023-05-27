/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:12:00 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/02 14:53:49 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	help_print(t_list *tmp, char *str)
{
	char	*content;
	char	*temp;
	char	*t;
	int		i;

	temp = ft_strjoin(str + 1, "\"");
	i = 0;
	while (tmp->data[i] && tmp->data[i] != '=')
		i++;
	content = ft_substr(tmp->data, 0, i + 1);
	t = content;
	content = ft_strjoin(content, "\"");
	free(t);
	t = content;
	content = ft_strjoin(content, temp);
	free(t);
	printf("declare -x %s\n", content);
	free(temp);
	free(content);
}

static void	print_export(t_list **export)
{
	t_list	*tmp;
	char	*str;

	tmp = *export;
	while (tmp)
	{
		str = ft_strchr(tmp->data, '=');
		if (!str)
		{
			str = ft_strdup(tmp->data);
			printf("declare -x %s\n", str);
			free(str);
		}
		else
			help_print(tmp, str);
		tmp = tmp->next;
	}
}

int	ft_export(t_list *cmd_line, t_list **envp, t_list **export)
{
	int		n;

	n = 0;
	if (!cmd_line->next)
		print_export(export);
	else if (cmd_line->next)
	{
		cmd_line = cmd_line->next;
		while (cmd_line)
		{
			if (cmd_line->token == WORD)
			{
				if (!valid_var(cmd_line->data, 'e', 2))
					n = 1;
				else
					if (!apply_export(envp, export, cmd_line->data))
						n = 1;
			}
			cmd_line = cmd_line->next;
		}
	}
	return (n);
}

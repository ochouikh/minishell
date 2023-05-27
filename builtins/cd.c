/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:33:22 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/25 16:16:23 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*ft_search_var(t_list *envp, char *str)
{
	t_list	*env;

	env = envp;
	while (env && ft_strncmp(str, env->data, ft_strlen(str)) != 0)
		env = env->next;
	if (env)
		return (ft_strdup(ft_strchr(env->data, '=') + 1));
	return (NULL);
}

static int	get_dir(char *dir)
{
	char	*err;

	if (dir && dir[0] == '\0')
		return (0);
	if (chdir(dir) == -1)
	{
		err = ft_strjoin("minishell: cd: ", dir);
		if (!err)
		{
			perror("strjoin()");
			return (1);
		}
		perror(err);
		free(err);
		return (1);
	}
	return (0);
}

int	ft_cd(t_list *cmd_line, t_list *envp, t_list *export)
{
	char	*dir;
	int		n;

	cmd_line = cmd_line->next;
	if (cmd_line && cmd_line->token == SP)
		cmd_line = cmd_line->next;
	if (!cmd_line)
	{
		dir = ft_search_var(envp, "HOME=");
		if (!dir)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	}
	else if (cmd_line && cmd_line->data && cmd_line->data[0] == '-'
		&& !cmd_line->data[1])
	{
		dir = ft_search_var(envp, "OLDPWD=");
		if (!dir)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
	}
	else
		dir = ft_strdup(cmd_line->data);
	n = get_dir(dir);
	change_on_pwd_and_oldpwd(envp, dir, 1);
	change_on_pwd_and_oldpwd(export, dir, 0);
	return (free(dir), n);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:07:47 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/18 16:31:49 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_list	*ft_search(t_list *envp, char *str)
{
	t_list	*env;
	char	*var;

	var = ft_strjoin(str, "=");
	env = envp;
	while (env && ft_strncmp(var, env->data, ft_strlen(var)) != 0)
		env = env->next;
	free(var);
	if (!env)
	{
		env = envp;
		while (env)
		{
			if (!ft_strchr(env->data, '=') && ft_strncmp(str, (env)->data,
					ft_max(ft_strlen(env->data), ft_strlen(str))) == 0)
				break ;
			env = env->next;
		}
	}
	return (env);
}

static void	edit_pwd(t_list *env_tmp, char *dir, int is_env)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (!str)
	{
		str = ft_strdup(dir);
		if (is_env)
			perror("cd: error retrieving current directory: \
getcwd: cannot access parent directories");
		if (dir[0] != '/')
		{
			free(str);
			str = ft_strjoin("/", dir);
		}
		free(env_tmp->data);
		env_tmp->data = ft_strjoin(env_tmp->data, str);
		free(str);
	}
	else
	{
		free(env_tmp->data);
		env_tmp->data = ft_strjoin("PWD=", str);
		free(str);
	}
}

void	change_on_pwd_and_oldpwd(t_list *envp, char *dir, int is_env)
{
	t_list	*old_pwd;
	t_list	*pwd;
	char	*str;

	old_pwd = ft_search(envp, "OLDPWD");
	pwd = ft_search(envp, "PWD");
	if (!pwd)
	{
		str = ft_strdup("PWD=");
		ft_lstadd_back(&envp, ft_lstnew(ENV, str));
		free(str);
		pwd = ft_search(envp, "PWD");
	}
	if (!old_pwd)
	{
		str = ft_strjoin("OLDPWD", ft_strchr(pwd->data, '='));
		ft_lstadd_back(&envp, ft_lstnew(ENV, str));
		free(str);
		old_pwd = ft_search(envp, "OLDPWD");
	}
	free(old_pwd->data);
	old_pwd->data = ft_strjoin("OLDPWD", ft_strchr(pwd->data, '='));
	edit_pwd(pwd, dir, is_env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:49:09 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/01 15:19:03 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_list	*case_env_exist(char **envp, int is_env)
{
	t_list	*new_env;
	int		i;

	new_env = NULL;
	i = 0;
	while (envp[i])
	{
		if (is_env && ft_strncmp(envp[i], "OLDPWD=", \
		ft_strlen("OLDPWD=")) == 0)
			i++;
		else if (!is_env && ft_strncmp(envp[i], "OLDPWD=", \
		ft_strlen("OLDPWD=")) == 0)
		{
			ft_lstadd_back(&new_env, ft_lstnew(ENV, "OLDPWD"));
			i++;
		}
		else
		{
			ft_lstadd_back(&new_env, ft_lstnew(ENV, envp[i]));
			i++;
		}
	}
	return (new_env);
}

t_list	*case_env_is_null(int is_env)
{
	t_list	*new_env;
	char	*str;
	char	*tmp;

	new_env = NULL;
	str = getcwd(NULL, 0);
	tmp = str;
	str = ft_strjoin("PWD=", str);
	free(tmp);
	ft_lstadd_back(&new_env, ft_lstnew(ENV, str));
	free(str);
	ft_lstadd_back(&new_env, ft_lstnew(ENV, "SHLVL=1"));
	if (is_env)
		ft_lstadd_back(&new_env, ft_lstnew(ENV, "_=/usr/bin/env"));
	if (!is_env)
		ft_lstadd_back(&new_env, ft_lstnew(ENV, "OLDPWD"));
	return (new_env);
}

t_list	*ft_envdup(char **envp, int is_env)
{
	if (envp && envp[0])
		return (case_env_exist(envp, is_env));
	return (case_env_is_null(is_env));
}

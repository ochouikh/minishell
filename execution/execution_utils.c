/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:19:04 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/27 17:13:40 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	command_not_found(char *s)
{
	ft_printf(2, "minishell: %s: command not found\n", s);
	exit(127);
}

char	*search_path(t_list *env)
{
	while (env && ft_strncmp(env->data, "PATH=", ft_strlen("PATH=")) != 0)
		env = env->next;
	if (env)
		return (env->data);
	return (NULL);
}

int	count_size(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		if (list->token == SP)
		{
			list = list->next;
			continue ;
		}
		list = list->next;
		i++;
	}
	return (i);
}

char	**list_to_array(t_list *list)
{
	char	**str;
	int		i;

	if (!list)
		return (NULL);
	str = malloc(sizeof(char *) * (count_size(list) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (list)
	{
		if (list->token == SP)
		{
			list = list->next;
			continue ;
		}
		str[i] = ft_strdup(list->data);
		list = list->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

void	shlvl(t_list **env)
{
	t_list	*env_tmp;

	env_tmp = *env;
	while (env_tmp
		&& ft_strncmp(env_tmp->data, "SHLVL=", ft_strlen("SHLVL=")) != 0)
		env_tmp = env_tmp->next;
	if (env_tmp)
	{
		if (ft_atoi(ft_strchr(env_tmp->data, '=') + 1) >= 1000)
		{
			ft_printf(2, "minishell: warning: shell level (%d) too high, \
			resetting to 1\n", ft_atoi(ft_strchr(env_tmp->data, '=') + 1) + 1);
			env_tmp->data = ft_strdup("SHLVL=1");
		}
		else if (ft_atoi(ft_strchr(env_tmp->data, '=') + 1) == 999)
			env_tmp->data = ft_strdup("SHLVL=");
		else if (ft_atoi(ft_strchr(env_tmp->data, '=') + 1) < 0)
			env_tmp->data = ft_strdup("SHLVL=0");
		else
			env_tmp->data = ft_strjoin("SHLVL=", \
			ft_itoa(ft_atoi(ft_strchr(env_tmp->data, '=') + 1) + 1));
	}
	else
		ft_lstadd_back(env, ft_lstnew(ENV, ft_strdup("SHLVL=1")));
}

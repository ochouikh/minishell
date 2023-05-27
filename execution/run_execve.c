/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 08:59:23 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/27 17:13:25 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exit_process(int exit_code, char **cmd)
{
	char	*str;

	str = ft_strjoin("minishell: ", cmd[0]);
	perror(str);
	free(str);
	exit(exit_code);
}

static void	path_case(t_list **env, char **cmd)
{
	char	**env_arr;

	if (ft_strchr(cmd[0], '/'))
	{
		if (ft_strncmp(cmd[0], "./minishell", \
		ft_max(ft_strlen(cmd[0]), ft_strlen("./minishell"))) == 0)
			shlvl(env);
		env_arr = list_to_array(*env);
		if (!env_arr)
			exit_process(1, env_arr);
		execve(cmd[0], cmd, env_arr);
		if (errno == EACCES)
			exit_process(126, cmd);
		else if (errno == ENOENT)
			exit_process(127, cmd);
		else
			exit_process(255, cmd);
	}
}

static void	cmd_case(char **cmd, char **env_arr, char *path_get)
{
	char	**str;
	char	*tmp;
	char	*path;

	str = ft_split(ft_strchr(path_get, '/'), ':');
	if (!str)
		command_not_found(cmd[0]);
	tmp = ft_strjoin("/", cmd[0]);
	while (*str)
	{
		path = ft_strjoin(*str, tmp);
		if (!access(path, F_OK | X_OK))
			break ;
		free(path);
		str++;
	}
	if (access(path, F_OK | X_OK) == -1)
		command_not_found(cmd[0]);
	execve(path, cmd, env_arr);
	if (errno == EACCES)
		exit_process(126, cmd);
	else if (errno == ENOENT)
		exit_process(127, cmd);
	else
		exit_process(255, cmd);
}

int	is_directory(char *data)
{
	DIR	*dir;

	if (!data)
		return (0);
	dir = opendir(data);
	if (!dir)
		return (0);
	return (1);
}

void	run_execve(t_list *node_content, t_list **env)
{
	char	**cmd;
	char	**env_arr;
	char	*path_var;

	if (*node_content->data == '\0' || is_directory(node_content->data))
		command_not_found(node_content->data);
	cmd = list_to_array(node_content);
	if (!cmd)
		exit_process(1, cmd);
	if (!*env)
		exit_process(127, cmd);
	path_case(env, cmd);
	env_arr = list_to_array(*env);
	if (!env_arr)
		exit_process(1, env_arr);
	path_var = search_path(*env);
	if (!path_var)
		exit_process(127, cmd);
	cmd_case(cmd, env_arr, path_var);
}

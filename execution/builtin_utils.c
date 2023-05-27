/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:04:22 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/15 16:51:47 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_empty_signal(int sig)
{
	(void)sig;
}

int	is_builtin(t_list *tokens)
{
	size_t	len;

	if (tokens && tokens->data)
	{
		len = ft_strlen(tokens->data);
		if (ft_strlen("echo") == len && !ft_strncmp(tokens->data, "echo", len))
			return (1);
		if (ft_strlen("cd") == len && !ft_strncmp(tokens->data, "cd", len))
			return (1);
		if (ft_strlen("pwd") == len && !ft_strncmp(tokens->data, "pwd", len))
			return (1);
		if (ft_strlen("export") == len
			&& !ft_strncmp(tokens->data, "export", len))
			return (1);
		if (ft_strlen("env") == len
			&& !ft_strncmp(tokens->data, "env", len) && !tokens->next)
			return (1);
		if (ft_strlen("unset") == len
			&& !ft_strncmp(tokens->data, "unset", len))
			return (1);
		if (ft_strlen("exit") == len && !ft_strncmp(tokens->data, "exit", len))
			return (1);
	}
	return (0);
}

int	call_builtin(t_list **env, t_list **export, t_list *cmd, int status)
{
	size_t	len;

	len = ft_strlen(cmd->data);
	if (ft_strlen("echo") == len && !ft_strncmp(cmd->data, "echo", len))
		status = ft_echo(cmd);
	else if (ft_strlen("cd") == len && !ft_strncmp(cmd->data, "cd", len))
		status = ft_cd(cmd, *env, *export);
	else if (ft_strlen("pwd") == len && !ft_strncmp(cmd->data, "pwd", len))
		status = ft_pwd(*env);
	else if (ft_strlen("export") == len
		&& !ft_strncmp(cmd->data, "export", len))
		status = ft_export(cmd, env, export);
	else if (ft_strlen("env") == len && !ft_strncmp(cmd->data, "env", len))
		status = ft_env(cmd, *env);
	else if (ft_strlen("unset") == len && !ft_strncmp(cmd->data, "unset", len))
		status = ft_unset(cmd, env, export);
	else if (ft_strlen("exit") == len && !ft_strncmp(cmd->data, "exit", len))
		status = ft_exit(cmd, status);
	return (status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:18:48 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/19 17:53:03 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static pid_t	protect_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int	process(t_pipe **fds, t_list **env, t_list **export, t_info infos)
{
	pid_t	pid;

	pid = protect_fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (dup2(infos.in, 0) == -1 || dup2(infos.out, 1) == -1)
			exit(EXIT_FAILURE);
		while ((*fds))
		{
			close((*fds)->read);
			close((*fds)->write);
			(*fds) = (*fds)->next;
		}
		if (redirections(infos.tree, *env))
			exit(1);
		if (is_builtin(infos.tree->data))
			exit(call_builtin(env, export, infos.tree->data, g_exit_status));
		else
			run_execve(infos.tree->data, env);
	}
	if (infos.if_wait || infos.tree == last_cmd_in_pipe(infos.tree))
		return (wait_lst_cmd(pid));
	return (0);
}

int	execute_cmd(t_pipe **fds, t_list **env, t_list **export, t_info infos)
{
	if (infos.tree && infos.tree->data
		&& is_builtin(infos.tree->data) && !parent_is_pipe(infos.tree))
	{
		if (redirections(infos.tree, *env))
			return (1);
		g_exit_status = call_builtin(env, export, infos.tree->data, \
		g_exit_status);
		close(0);
		close(1);
		if (open(ttyname(STDERR_FILENO), O_RDONLY) == -1
			|| open(ttyname(STDERR_FILENO), O_WRONLY) == -1)
		{
			perror("open()");
			exit(EXIT_FAILURE);
		}
	}
	else if (infos.tree && infos.tree->data)
		g_exit_status = process(fds, env, export, infos);
	return (g_exit_status);
}

int	case_pipe(t_pipe **fds, t_list **env, t_list **export, t_info infos)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe()");
		exit(EXIT_FAILURE);
	}
	pipe_lstadd_back(fds, pipe_lstnew(fd));
	traverse_tree(fds, env, export, \
	assign_infos(0, infos.in, fd[1], infos.tree->left));
	close(fd[1]);
	g_exit_status = traverse_tree(fds, env, export, \
	assign_infos(0, fd[0], infos.out, infos.tree->right));
	close(fd[0]);
	return (g_exit_status);
}

int	traverse_tree(t_pipe **fds, t_list **env, t_list **export, t_info infos)
{
	init_signals();
	if (!infos.tree)
		return (g_exit_status);
	if (infos.tree->token == PIPE)
		g_exit_status = case_pipe(fds, env, export, infos);
	else if (infos.tree->token == AND)
	{
		g_exit_status = traverse_tree(fds, env, export, \
		assign_infos(1, infos.in, infos.out, infos.tree->left));
		if (g_exit_status == 0)
			g_exit_status = traverse_tree(fds, env, export, \
			assign_infos(1, infos.in, infos.out, infos.tree->right));
	}
	else if (infos.tree->token == OR)
	{
		g_exit_status = traverse_tree(fds, env, export, \
		assign_infos(1, infos.in, infos.out, infos.tree->left));
		if (g_exit_status > 0)
			g_exit_status = traverse_tree(fds, env, export, \
			assign_infos(1, infos.in, infos.out, infos.tree->right));
	}
	else
		if (expander(infos.tree, infos.tree->data, *env))
			g_exit_status = execute_cmd(fds, env, export, infos);
	return (g_exit_status);
}

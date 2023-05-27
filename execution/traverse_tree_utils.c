/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_tree_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:36:17 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/15 16:50:41 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	init_signals(void)
{
	signal(SIGINT, ft_empty_signal);
	signal(SIGQUIT, ft_empty_signal);
}

int	parent_is_pipe(t_tree *root)
{
	while (root->parent)
	{
		if (root->parent->token == PIPE)
			return (1);
		root = root->parent;
	}
	return (0);
}

t_tree	*last_cmd_in_pipe(t_tree *root)
{
	while (root->parent && root->parent->token == PIPE)
		root = root->parent;
	return (root->right);
}

t_info	assign_infos(int if_wait, int in, int out, t_tree *root)
{
	t_info	infos;

	infos.if_wait = if_wait;
	infos.in = in;
	infos.out = out;
	infos.tree = root;
	return (infos);
}

int	wait_lst_cmd(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		exit (EXIT_FAILURE);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (WTERMSIG(status) + 128);
}

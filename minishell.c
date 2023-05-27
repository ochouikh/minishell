/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:20:36 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/26 09:43:03 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 1;
	}
}

void	free_tree_or_fds(t_tree *root, t_pipe *fds, char c)
{
	t_pipe	*tmp;

	if (c == 't')
	{
		if (!root)
			return ;
		free_tree_or_fds(root->left, fds, 't');
		free_tree_or_fds(root->right, fds, 't');
		free_list(root->data);
		free(root);
	}
	else if (c == 'f')
	{
		while (fds)
		{
			tmp = fds->next;
			free(fds);
			fds = tmp;
		}
	}
}

void	initialize_infos(t_info *infos, char **envp)
{
	infos->line = NULL;
	infos->env = NULL;
	infos->export = NULL;
	g_exit_status = 0;
	infos->if_wait = 1;
	infos->in = 0;
	infos->out = 1;
	infos->heredoc_files = NULL;
	if (!infos->env)
		infos->env = ft_envdup(envp, 1);
	if (!infos->export)
		infos->export = ft_envdup(envp, 0);
}

int	build_tree_and_execute(t_info infos, t_list **envp, t_list **export)
{
	t_pipe	*fds;

	fds = NULL;
	if (infos.invalid_input)
		g_exit_status = infos.invalid_input;
	if (!infos.invalid_input)
	{
		search_heredoc(infos.tokens, &infos.heredoc_files);
		infos.tree = build_tree(infos.tokens);
		if (ttyname(STDIN_FILENO) == NULL)
			open(ttyname(STDERR_FILENO), O_RDONLY);
		else
			g_exit_status = traverse_tree(&fds, envp, \
			export, infos);
		while (wait(0) != -1)
			;
	}
	free_tree_or_fds(infos.tree, fds, 't');
	free_tree_or_fds(infos.tree, fds, 'f');
	unlink_tmp_files(infos.heredoc_files);
	return (g_exit_status);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_info	infos;

	(void)argv;
	initialize_infos(&infos, envp);
	rl_catch_signals = 0;
	if (argc != 1)
		return (g_exit_status);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_ctrlc);
		infos.tree = NULL;
		infos.line = readline("minishell$ ");
		if (!infos.line)
			break ;
		add_history(infos.line);
		infos.tokens = tokenization(infos.line, NULL);
		infos.invalid_input = parsing(&infos.tokens, &infos, 0);
		g_exit_status = build_tree_and_execute(infos, &infos.env, \
		&infos.export);
		free(infos.line);
		free_list(infos.tokens);
	}
	printf("exit\n");
	return (g_exit_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:16:09 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/10 21:31:21 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"
# include <fcntl.h>
# include <errno.h>

typedef struct s_info	t_info;
typedef struct s_pipe	t_pipe;

int		traverse_tree(t_pipe **fds, t_list **env, \
t_list **export, t_info infos);
void	run_execve(t_list *node_content, t_list **env);
int		redirections(t_tree *root, t_list *env);
int		is_builtin(t_list *tokens);
int		call_builtin(t_list **env, t_list **export, t_list *cmd, int status);
void	command_not_found(char *s);
void	exit_process(int exit_code, char **cmd);
char	*search_path(t_list *env);
char	**list_to_array(t_list *list);
void	shlvl(t_list **env);
int		parent_is_pipe(t_tree *root);
t_tree	*last_cmd_in_pipe(t_tree *root);
t_info	assign_infos(int if_wait, int in, int out, t_tree *root);
int		wait_lst_cmd(pid_t pid);
void	init_signals(void);
void	ft_empty_signal(int sig);

#endif

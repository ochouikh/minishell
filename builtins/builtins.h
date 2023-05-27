/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:02:48 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/18 17:51:20 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

t_list	*ft_envdup(char **envp, int is_env);
int		ft_echo(t_list *cmd_line);
int		ft_cd(t_list *cmd_line, t_list *envp, t_list *export);
void	change_on_pwd_and_oldpwd(t_list *envp, char *dir, int is_env);
int		ft_pwd(t_list *envp);
int		ft_export(t_list *cmd_line, t_list **envp, t_list **export);
t_list	*ft_search_for_var(t_list **envp, char *tab, char *str, int i);
void	ft_replace_eq(t_list **envp, t_list *tmp, char *tab);
void	ft_replace_add(t_list **envp, t_list *tmp, char *tab, int i);
int		valid_var(char *s, char c, int type);
int		apply_export(t_list **envp, t_list **export, char *s);
int		ft_env(t_list *cmd_line, t_list *env);
int		ft_unset(t_list *cmd_line, t_list **envp, t_list **export);
int		ft_exit(t_list *cmd_line, int status);
int		ft_max(int i, int j);

#endif
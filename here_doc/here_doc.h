/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:00:45 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/09 11:31:51 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "../minishell.h"

void	search_heredoc(t_list *tokens, t_list **heredoc_files);
void	concate_and_open(t_list **tokens, t_list **heredoc_files, t_list *tmp2);
void	open_heredoc_file(t_list *lst, int quote, t_list **heredoc_files);
char	*find_correct_file(int quote);
void	open_tmp_file(char *name, char *limit);
int		is_equal(char *s1, char *s2, int limit_len);
void	finish_prompt(int sig);
void	unlink_tmp_files(t_list *heredoc_files);
void	open_tmp_file(char *name, char *limit);

#endif
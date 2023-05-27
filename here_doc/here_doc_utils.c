/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:04:22 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/15 17:11:53 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

void	finish_prompt(int sig)
{
	if (sig == SIGINT)
		close(0);
}

int	is_equal(char *s1, char *s2, int limit_len)
{
	int	len1;

	len1 = ft_strlen(s1);
	if (len1 == limit_len && ft_strncmp(s1, s2, len1) == 0)
		return (1);
	return (0);
}

void	open_tmp_file(char *name, char *limit)
{
	int		tmp_fd;
	char	*s;
	int		limit_len;

	limit_len = ft_strlen(limit);
	tmp_fd = open(name, O_CREAT | O_RDWR, 0600);
	if (tmp_fd == -1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, finish_prompt);
	s = readline("> ");
	while ((s && !is_equal(s, limit, limit_len)
			&& ttyname(STDIN_FILENO) != NULL)
		|| ((s && s[0] == '\0') && *limit != '\0'))
	{
		ft_printf(tmp_fd, "%s\n", s);
		free(s);
		s = readline("> ");
	}
	if (s && is_equal(s, limit, limit_len))
		free(s);
	close(tmp_fd);
}

void	unlink_tmp_files(t_list *heredoc_files)
{
	t_list	*tmp;

	while (heredoc_files)
	{
		unlink(heredoc_files->data);
		free(heredoc_files->data);
		tmp = heredoc_files;
		heredoc_files = heredoc_files->next;
		free(tmp);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:24:26 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/15 17:09:12 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	count_lines(char *file)
{
	int		fd;
	char	*s;
	int		i;

	fd = open(file, O_RDONLY);
	s = get_next_line(fd);
	i = 0;
	while (s)
	{
		free(s);
		s = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

static char	*get_line_expand(t_list *env, char *str, int fd)
{
	char	*tmp;

	str = get_next_line(fd);
	tmp = str;
	str = search_and_expand(env, str);
	free(tmp);
	return (str);
}

static char	**expand_buff(char *file, t_list *env, int i)
{
	char	**buff;
	int		fd;
	int		j;

	buff = (char **)malloc((i + 1) * sizeof(char *));
	if (!buff)
	{
		perror("malloc()");
		exit(EXIT_FAILURE);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	j = -1;
	while (++j < i)
		buff[j] = get_line_expand(env, buff[j], fd);
	buff[j] = NULL;
	close(fd);
	unlink(file);
	return (buff);
}

void	expand_heredoc(char *file, t_list *env)
{
	int		i;
	int		j;
	int		fd;
	char	**buff;

	if (file[1] == 'q')
		return ;
	i = count_lines(file);
	buff = expand_buff(file, env, i);
	fd = open(file, O_CREAT | O_RDWR, 0600);
	if (fd == -1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	j = -1;
	while (++j < i)
	{
		ft_printf(fd, "%s", buff[j]);
		free(buff[j]);
	}
	free(buff);
	close(fd);
}

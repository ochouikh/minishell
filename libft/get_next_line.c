/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:32:32 by ochouikh          #+#    #+#             */
/*   Updated: 2023/01/30 19:37:59 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_join(char *buffer, char *to_read)
{
	char	*t;

	t = ft_strjoin_get(buffer, to_read);
	free(buffer);
	return (t);
}

char	*ft_get_next(char *str)
{
	int		i;
	char	*next;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	i++;
	next = ft_substr_get(str, i, ft_strlen(str) - i);
	free(str);
	return (next);
}

char	*ft_get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	line = ft_substr_get(str, 0, i + 1);
	return (line);
}

char	*ft_get_read(int fd, char *buffer)
{
	char	*to_read;
	int		r;

	to_read = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!to_read)
		return (NULL);
	r = 1;
	while (r > 0)
	{
		r = read(fd, to_read, BUFFER_SIZE);
		if (r < 0)
		{
			free(to_read);
			free(buffer);
			return (NULL);
		}
		to_read[r] = '\0';
		buffer = ft_get_join(buffer, to_read);
		if (ft_strchr(to_read, '\n'))
			break ;
	}
	free(to_read);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_get_read(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	buffer = ft_get_next(buffer);
	return (line);
}

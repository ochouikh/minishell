/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:24:06 by ochouikh          #+#    #+#             */
/*   Updated: 2023/04/21 10:54:11 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s, int fd)
{
	int	i;

	if (s == NULL)
	{
		if (write(1, "(null)", 6) == -1)
			perror("write");
		return (6);
	}
	i = 0;
	while (s[i])
		i++;
	if (write(fd, s, i) == -1)
		perror("write");
	return (i);
}

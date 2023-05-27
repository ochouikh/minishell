/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:43:51 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/18 17:53:51 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	in_string(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_number(char n)
{
	return (n >= '0' && n <= '9');
}

int	is_space(char n)
{
	return (in_string(n, " \n\t\v\r\f"));
}

int	ft_atoi(const char *str)
{
	int	result;
	int	signe;
	int	save;
	int	i;

	result = 0;
	signe = 1;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-')
		signe *= -1;
	if ((str[i] == '+') || (str[i] == '-'))
		i++;
	while (is_number(str[i]))
	{
		save = result;
		result *= 10;
		result += str[i] - '0';
		if (save != result / 10)
			return (-1);
		i++;
	}
	return (result * signe);
}

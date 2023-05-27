/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:06:29 by ochouikh          #+#    #+#             */
/*   Updated: 2022/10/21 16:53:41 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	l;
	char	*str;

	l = ft_strlen(s) + 1;
	i = 0;
	while (i < l)
	{
		if (s[i] == (unsigned char)c)
		{
			str = (char *)(s + i);
			return (str);
		}
		i++;
	}
	return (NULL);
}

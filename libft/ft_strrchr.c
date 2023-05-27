/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:13:18 by ochouikh          #+#    #+#             */
/*   Updated: 2022/10/21 16:53:45 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	l;
	char	*str;

	str = NULL;
	l = ft_strlen(s) + 1;
	i = 0;
	while (i < l)
	{
		if (s[i] == (unsigned char)c)
		{
			str = (char *)(s + i);
		}
		i++;
	}
	return (str);
}

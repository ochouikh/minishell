/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:30:05 by ochouikh          #+#    #+#             */
/*   Updated: 2023/02/06 13:41:42 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	in_set(char const c, char const *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (c == s[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	first;
	size_t	last;

	if (s1 == NULL)
		return (NULL);
	first = 0;
	last = ft_strlen(s1);
	while (s1[first] && in_set(s1[first], set))
		first++;
	while (last > first && in_set(s1[last - 1], set))
		last--;
	str = (char *)malloc((last - first) * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (first < last)
	{
		str[i] = s1[first];
		i++;
		first++;
	}
	str[i] = '\0';
	return (str);
}

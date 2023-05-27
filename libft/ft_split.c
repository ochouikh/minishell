/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:06:17 by ochouikh          #+#    #+#             */
/*   Updated: 2022/10/25 14:01:50 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_len_str(char const *s, char c)
{
	size_t	i;
	size_t	n;
	int		j;

	i = 0;
	n = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			j = 1;
		else if (s[i] == c && j == 1)
		{
			j = 0;
			n++;
		}
		i++;
	}
	if (j == 1)
		n++;
	return (n);
}

char	**ft_alloc_ptr(char **str, char const *s, char c, size_t n)
{
	size_t	i;
	size_t	k;
	size_t	j;

	i = 0;
	k = 0;
	while (i < ft_strlen(s) && k < n - 1)
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[j] != c && s[j] != '\0')
			j++;
		str[k] = (char *)malloc((j - i) * sizeof(char) + 1);
		if (str[k] == NULL)
		{
			while (k >= 0)
				free(str[--k]);
			return (NULL);
		}
		k++;
		i = j;
	}
	return (str);
}

char	**ft_affich(char **str, char const *s, char c, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (i < ft_strlen(s) && j < n - 1)
	{
		k = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			str[j][k] = s[i];
			i++;
			k++;
		}
		str[j][k] = '\0';
		j++;
	}
	str[j] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	n;

	if (s == NULL)
		return (NULL);
	if (s[0] == '\0')
	{
		str = (char **)malloc(1);
		str[0] = NULL;
		return (str);
	}
	n = ft_len_str(s, c) + 1;
	str = (char **)malloc(sizeof(char *) * (n));
	if (str == NULL)
		return (NULL);
	str = ft_alloc_ptr(str, s, c, n);
	ft_affich(str, s, c, n);
	return (str);
}

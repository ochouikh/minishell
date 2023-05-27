/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:05:02 by ochouikh          #+#    #+#             */
/*   Updated: 2022/10/21 08:52:18 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n;

	if (needle[0] == 0)
		return ((char *)haystack);
	n = ft_strlen(needle);
	i = 0;
	while (i < len && haystack[i] != '\0')
	{
		if (haystack[i] == (char)needle[0] && len - i >= n
			&& ft_strncmp(haystack + i, needle, n) == 0)
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}

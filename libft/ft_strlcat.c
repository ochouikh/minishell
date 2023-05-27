/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:26:38 by ochouikh          #+#    #+#             */
/*   Updated: 2022/10/16 14:52:53 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	n;

	if (dst == 0 && dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (dst[i] != '\0')
		i++;
	n = i;
	if (dstsize != 0 && n < dstsize)
	{
		i = 0;
		while (i < dstsize - 1 - n && src[i] != '\0')
		{
			dst[i + n] = src[i];
			i++;
		}
		dst[i + n] = '\0';
		return (n + ft_strlen(src));
	}
	return (ft_strlen(src) + dstsize);
}

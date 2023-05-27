/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:51:42 by ochouikh          #+#    #+#             */
/*   Updated: 2023/04/21 10:43:34 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n, int fd)
{
	int	c;

	c = 0;
	if (n == -2147483648)
		c = ft_putstr("-2147483648", fd);
	else if (n < 0)
	{
		c += ft_putchar('-', fd);
		c += ft_putnbr(-n, fd);
	}
	else if (n < 10)
		c += ft_putchar(n + '0', fd);
	else
	{
		c += ft_putnbr(n / 10, fd);
		c += ft_putnbr(n % 10, fd);
	}
	return (c);
}

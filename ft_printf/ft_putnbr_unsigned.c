/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:51:42 by ochouikh          #+#    #+#             */
/*   Updated: 2023/04/21 10:44:12 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_unsigned(unsigned int n, int fd)
{
	int	c;

	c = 0;
	if (n >= 0 && n < 10)
		c += ft_putchar(n + '0', fd);
	else
	{
		c += ft_putnbr_unsigned(n / 10, fd);
		c += ft_putnbr_unsigned(n % 10, fd);
	}
	return (c);
}

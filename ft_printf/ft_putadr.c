/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 13:20:21 by ochouikh          #+#    #+#             */
/*   Updated: 2023/04/21 10:45:19 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putadr(unsigned long long n, char *base, int fd)
{
	int	c;

	c = 0;
	if (n < 16)
		c += ft_putchar(base[(int)(n)], fd);
	else
	{
		c += ft_putadr(n / 16, base, fd);
		c += ft_putadr(n % 16, base, fd);
	}
	return (c);
}

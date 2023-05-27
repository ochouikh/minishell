/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:56:34 by ochouikh          #+#    #+#             */
/*   Updated: 2022/11/06 16:56:34 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check(va_list arg, char c, int fd)
{
	int	n;

	n = 0;
	if (c == 'd' || c == 'i')
		n += ft_putnbr(va_arg(arg, int), fd);
	else if (c == 'c')
		n += ft_putchar(va_arg(arg, int), fd);
	else if (c == 's')
		n += ft_putstr(va_arg(arg, char *), fd);
	else if (c == 'p')
	{
		n += ft_putstr("0x", fd);
		n += ft_putadr(va_arg(arg, unsigned long long), "0123456789abcdef", fd);
	}
	else if (c == 'u')
		n += ft_putnbr_unsigned(va_arg(arg, unsigned int), fd);
	else if (c == 'x')
		n += ft_putnbr_base(va_arg(arg, unsigned int), "0123456789abcdef", fd);
	else if (c == 'X')
		n += ft_putnbr_base(va_arg(arg, unsigned int), "0123456789ABCDEF", fd);
	else if (c == '%')
		n += ft_putchar('%', fd);
	else
		n += ft_putchar(c, fd);
	return (n);
}

int	ft_printf(int fd, const char *str, ...)
{
	va_list	arg;
	int		j;
	int		count;

	va_start(arg, str);
	count = 0;
	j = 0;
	while (str[j] != '\0')
	{
		if (str[j] == '%')
		{
			if (str[j + 1] == '\0')
				return (count);
			count += ft_check(arg, str[j + 1], fd);
			j++;
		}
		else
			count += ft_putchar(str[j], fd);
		j++;
	}
	va_end(arg);
	return (count);
}

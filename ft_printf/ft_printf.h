/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:57:18 by ochouikh          #+#    #+#             */
/*   Updated: 2022/11/06 16:57:18 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

int	ft_printf(int fd, const char *str, ...);
int	ft_putchar(int c, int fd);
int	ft_putstr(char *s, int fd);
int	ft_putnbr(int n, int fd);
int	ft_putnbr_unsigned(unsigned int n, int fd);
int	ft_putnbr_base(unsigned int n, char *base, int fd);
int	ft_putadr(unsigned long long n, char *base, int fd);

#endif

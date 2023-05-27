/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:34:47 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/10 15:39:55 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_syntax_error(char *s)
{
	ft_printf(2, "minishell: syntax error near unexpected token `%s'\n", s);
	return (258);
}

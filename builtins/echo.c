/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:37:52 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/09 15:50:57 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_is_option_n(char *cmd)
{
	int	i;

	if (cmd && cmd[0] == '-' && cmd[1])
	{
		i = 1;
		while (cmd[i] && cmd[i] == 'n')
			i++;
		if (!cmd[i])
			return (1);
	}
	return (0);
}

static void	print_content(t_list *cmd_line)
{
	if (cmd_line && cmd_line->token == SP)
		cmd_line = cmd_line->next;
	while (cmd_line)
	{
		if (cmd_line->token == WORD)
			ft_putstr_fd(cmd_line->data, 1);
		else if (cmd_line->token == SP)
			ft_putstr_fd(" ", 1);
		cmd_line = cmd_line->next;
	}
}

int	ft_echo(t_list *cmd_line)
{
	int		nl;

	nl = 1;
	cmd_line = cmd_line->next;
	while (cmd_line && (cmd_line->token == SP
			|| (cmd_line->data && ft_is_option_n(cmd_line->data))))
	{
		if (cmd_line && ft_is_option_n(cmd_line->data))
		{
			cmd_line = cmd_line->next;
			nl = 0;
		}
		else
			cmd_line = cmd_line->next;
	}
	print_content(cmd_line);
	if (nl == 1)
		ft_putstr_fd("\n", 1);
	return (0);
}

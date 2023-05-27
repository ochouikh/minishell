/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:50:58 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/18 17:58:34 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_and_exit(int exit_num)
{
	printf("exit\n");
	exit(exit_num);
}

static int	is_number(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_list *cmd_line, int status)
{
	if (!cmd_line->next)
		print_and_exit(status);
	else
	{
		cmd_line = cmd_line->next->next;
		if (!cmd_line->next && (is_number(cmd_line->data) || (cmd_line->data[0]
					&& cmd_line->data[0] == '-' && cmd_line->data[1]
					&& is_number(cmd_line->data + 1))))
			print_and_exit(ft_atoi(cmd_line->data));
		else if (!is_number(cmd_line->data))
		{
			ft_printf(2, "exit\nminishell: exit: %s: \
numeric argument required\n", cmd_line->data);
			exit(255);
		}
		if (cmd_line->next)
		{
			ft_printf(2, "exit\nminishell: exit: too many arguments\n");
			status = 1;
		}
	}
	return (status);
}

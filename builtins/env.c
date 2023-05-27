/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:41:03 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/18 14:21:52 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_list *cmd_line, t_list *env)
{
	if (!cmd_line->next)
	{
		while (env)
		{
			printf("%s\n", env->data);
			env = env->next;
		}
	}
	return (0);
}

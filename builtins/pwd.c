/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:41:17 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/01 12:50:15 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_list *envp)
{
	char	*pwd;
	t_list	*tmp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		tmp = envp;
		while (tmp && ft_strncmp("PWD=", tmp->data, ft_strlen("PWD=")) != 0)
			tmp = tmp->next;
		if (tmp)
			pwd = ft_strdup(ft_strchr(tmp->data, '=') + 1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

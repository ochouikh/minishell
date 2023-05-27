/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_lstadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:19:27 by ochouikh          #+#    #+#             */
/*   Updated: 2023/04/29 15:22:04 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void	pipe_lstadd_back(t_pipe **lst, t_pipe *new)
{
	t_pipe	*ptr;

	ptr = *lst;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
}

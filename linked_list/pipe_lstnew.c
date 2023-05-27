/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_lstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochouikh <ochouikh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:17:31 by ochouikh          #+#    #+#             */
/*   Updated: 2023/05/04 21:19:26 by ochouikh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

t_pipe	*pipe_lstnew(int fd[2])
{
	t_pipe	*head;

	head = malloc(sizeof(t_pipe));
	if (head == NULL)
		return (NULL);
	head->read = fd[0];
	head->write = fd[1];
	head->next = NULL;
	return (head);
}

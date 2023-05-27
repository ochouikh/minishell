/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:18:46 by mel-aini          #+#    #+#             */
/*   Updated: 2023/03/27 17:16:31 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

t_list	*ft_lstnew(int token, char *data)
{
	t_list	*head;

	head = malloc(sizeof(t_list));
	if (head == NULL)
		return (NULL);
	head->prev = NULL;
	head->token = token;
	head->data = ft_strdup(data);
	head->next = NULL;
	return (head);
}

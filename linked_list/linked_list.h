/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-aini <mel-aini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:42:27 by mel-aini          #+#    #+#             */
/*   Updated: 2023/05/06 18:01:05 by mel-aini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include "../minishell.h"

typedef struct s_list
{
	struct s_list	*prev;
	int				token;
	char			*data;
	struct s_list	*next;
}				t_list;

typedef struct s_pipe
{
	int				read;
	int				write;
	struct s_pipe	*next;
}				t_pipe;

t_list	*ft_lstnew(int token, char *data);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_pipe	*pipe_lstnew(int fd[2]);
void	pipe_lstadd_back(t_pipe **lst, t_pipe *new);

#endif
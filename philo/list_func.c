/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:41:26 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/29 17:01:24 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philosopher	*ft_lstnew(t_args **args, int id)
{
	t_philosopher	*new_lst;

	new_lst = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (!new_lst)
		return (NULL);
	new_lst->thread = NULL;
	new_lst->args = *args;
	new_lst->thread_id = id;
	new_lst->eating = (*args)->notepme;
	new_lst->last_eat = 0;
	new_lst->death = 0;
	new_lst->next = NULL;
	return (new_lst);
}

t_philosopher	*ft_lstlast(t_philosopher *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_philosopher **lst, t_philosopher *new)
{
	t_philosopher	*node;

	if (new != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			node = *lst;
			while (node->next != NULL)
				node = node->next;
		node->next = new;
		}
	}
}

void	ft_lstdelone(t_philosopher *lst, void (*del)(void*))
{
	if (lst != NULL && *del != NULL)
	{
		free(lst);
	}
}

void	ft_lstclear(t_philosopher **lst, void (*del)(void*))
{
	t_philosopher	*node;

	if (*lst != NULL && del != NULL)
	{
		node = *lst;
		while (node != *lst)
		{
			ft_lstdelone(node, del);
			node = node->next;
		}
		*lst = NULL;
	}
}
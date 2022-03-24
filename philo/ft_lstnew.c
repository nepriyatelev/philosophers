/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:23:19 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/24 19:45:57 by modysseu         ###   ########.fr       */
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
	new_lst->count_eat = (*args)->notepme;
	new_lst->is_dead = 0;
	new_lst->next = NULL;
	return (new_lst);
}

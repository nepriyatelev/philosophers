/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:23:19 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/22 14:26:26 by modysseu         ###   ########.fr       */
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
	new_lst->is_dead = 0;
	new_lst->ttd = new_lst->args->ttd;
	new_lst->next = NULL;
	return (new_lst);
}

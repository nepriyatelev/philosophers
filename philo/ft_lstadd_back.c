/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:25:36 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/16 20:57:19 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

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
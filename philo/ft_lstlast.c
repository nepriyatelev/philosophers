/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:24:54 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/20 16:25:27 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philosopher	*ft_lstlast(t_philosopher *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

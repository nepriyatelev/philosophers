/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:23:23 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/28 15:49:58 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_lst(t_philosopher **thread, t_args **args)
{
	int				i;
	t_philosopher	*tmp;

	tmp = NULL;
	i = 0;
	while (i < (*args)->nop)
	{
		tmp = ft_lstnew(args, i + 1);
		if (tmp == NULL)
			return (1);
		ft_lstadd_back(thread, tmp);
		i++;
	}
	ft_lstlast(*thread)->next = *thread;
	return (0);
}
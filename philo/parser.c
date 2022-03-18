/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:48:39 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/18 17:27:19 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	validation_check(char **input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		j = 0;
		if (ft_atoi(input[i]) == 0)
			return (1);
		while (input[i][j])
		{
			if (ft_isdigit(input[i][j]))
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	parser(t_arg *param, char **input)
{
	if (validation_check(input))
		return (1);
	param->number_of_philosophers = ft_atoi(input[0]);
	param->time_to_die = ft_atoi(input[1]);
	param->time_to_eat = ft_atoi(input[2]);
	param->time_to_sleep = ft_atoi(input[3]);
	if (input[4])
		param->number_of_times_each_philosopher_must_eat = ft_atoi(input[4]);
	else
		param->number_of_times_each_philosopher_must_eat = 0;
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:48:39 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/16 21:01:44 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	validation_check(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		if (ft_atoi(argv[i]) == 0)
			return (1);
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]))
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	parser(t_arg *param, char **argv)
{
	if (validation_check(argv))
		return (1);
	param->number_of_philosophers = ft_atoi(argv[0]);
	param->time_to_die = ft_atoi(argv[1]);
	param->time_to_eat = ft_atoi(argv[2]);
	param->time_to_sleep = ft_atoi(argv[3]);
	if (argv[4])
		param->number_of_times_each_philosopher_must_eat = ft_atoi(argv[4]);
	else
		param->number_of_times_each_philosopher_must_eat = 0;
	return (0);
}
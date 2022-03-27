/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:48:39 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/27 21:00:32 by modysseu         ###   ########.fr       */
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
			return (ERROR_INPUT);
		while (input[i][j])
		{
			if (ft_isdigit(input[i][j]))
				j++;
			else
				return (ERROR_INPUT);
		}
		i++;
	}
	return (0);
}

int	parser(t_args *args, char **input)
{
	if (validation_check(input))
		return (ERROR_INPUT);
	args->nop = ft_atoi(input[0]);
	args->ttd = ft_atoi(input[1]);
	args->tte = ft_atoi(input[2]);
	args->tts = ft_atoi(input[3]);
	if (input[4])
		args->notepme = ft_atoi(input[4]);
	else
		args->notepme = 0;
	args->start_time = 0;
	return (0);
}
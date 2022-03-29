/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:48:39 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/28 18:12:55 by modysseu         ###   ########.fr       */
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

int	parser(t_args *args, char **input)
{
	if (validation_check(input))
		return (1);
	args->nop = ft_atoi(input[0]);
	args->ttd = ft_atoi(input[1]);
	args->tte = ft_atoi(input[2]);
	args->tts = ft_atoi(input[3]);
	if (input[4])
		args->notepme = ft_atoi(input[4]);
	else
		args->notepme = -1;
	args->start_time = 0;
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:48:39 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/25 17:17:09 by modysseu         ###   ########.fr       */
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

int	parser(t_philosopher **thread, char **input)
{
	t_args	*args;

	args = (t_args *)malloc(sizeof(t_args));
	if (args == NULL)
		return (1);
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
	if (init_lst(thread, &args))
		return (1);
	return (0);
}
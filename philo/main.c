/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:19:48 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/16 21:02:24 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_arg	arg;

	if (argc != 5 && argc != 6)
		return (1);
	else
		if (parser(&arg, argv + 1))
			return (1);
	return (0);
}


	// printf("%d\n", param.number_of_philosophers);
	// printf("%d\n", param.time_to_die);
	// printf("%d\n", param.time_to_eat);
	// printf("%d\n", param.time_to_sleep);
	// printf("%d\n", param.number_of_times_each_philosopher_must_eat);
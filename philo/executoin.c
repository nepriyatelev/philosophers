/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executoin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:24:25 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/29 18:46:31 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	for_norm(t_philosopher *thread, long long time_to_print)
{
	if (thread->args->nop != 1)
		starts_to_sleep(thread, time_to_print);
	if (thread->args->nop != 1)
		begins_to_think(thread, time_to_print);
}

void	*execution(void *incoming_thread)
{
	t_philosopher	*thread;
	long long		time_to_print;
	long long		check_time;

	check_time = 0;
	time_to_print = 0;
	thread = (t_philosopher *)incoming_thread;
	while (1)
	{
		if (thread->death != 1)
			take_your_fork(thread, time_to_print);
		if (thread->args->nop != 1)
			starts_eating(thread, time_to_print);
		else
			ft_sleep(thread->args->ttd);
		checking_the_status(thread, check_time);
		ft_sleep(thread->args->tte);
		pthread_mutex_unlock(&thread->fork);
		if (thread->args->nop != 1)
			pthread_mutex_unlock(&thread->next->fork);
		for_norm(thread, time_to_print);
	}
	return (NULL);
}

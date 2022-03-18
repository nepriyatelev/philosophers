/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:19:48 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/18 21:58:36 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *execution(void *incoming_thread)
{
	usleep(100);
	t_philosopher	*thread;
	
	thread = (t_philosopher *)incoming_thread;
	pthread_mutex_lock(&thread->fork);
	printf("%d has taken a fork\n", thread->thread_id);
	printf("%d is eating\n", thread->thread_id);
	pthread_mutex_unlock(&thread->fork);
	sleep(4);
	while (1)
	{
		printf("%d is sleeping\n", thread->thread_id);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_arg			input;
	t_philosopher	*thread;
	int				i;

	thread = (t_philosopher *)malloc(sizeof(t_philosopher) * input.number_of_philosophers);
	i = 0;
	if (argc != 5 && argc != 6)
		return (1);
	else
		if (parser(&input, argv + 1))
			return (1);
	while (i < input.number_of_philosophers)
	{
		thread[i].thread_id = i + 1;
		thread[i].input = &input;
		if (pthread_mutex_init(&thread[i].fork, NULL))
			return (1);
		i++;
	}
	i = 0;
	while (i < input.number_of_philosophers)
	{
		if (pthread_create(&thread[i].thread, NULL, &execution, &thread[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < input.number_of_philosophers)
	{
		if (pthread_join(thread[i].thread, NULL))
			return (1);
		i++;
	}
	i = 0;
	free(thread);
	return (0);
}


	// printf("%d\n", arg.number_of_philosophers);
	// printf("%d\n", arg.time_to_die);
	// printf("%d\n", arg.time_to_eat);
	// printf("%d\n", arg.time_to_sleep);
	// printf("%d\n", arg.number_of_times_each_philosopher_must_eat);
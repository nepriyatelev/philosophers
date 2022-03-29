/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:19:48 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/29 18:52:52 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	if_death(t_philosopher *thread, int death)
{
	long long	time_to_print;

	time_to_print = 0;
	pthread_mutex_lock(&thread->args->print);
	pthread_mutex_lock(&thread->args->data);
	time_to_print = ft_gettime() - thread->args->start_time;
	if (death)
		printf("%llu ms : philosopher %d is death\n", \
			time_to_print, thread->thread_id);
	else
		printf("%llu ms : philosopher ate everything\n", time_to_print);
	thread_detatch(thread);
	pthread_mutex_unlock(&thread->args->data);
	pthread_mutex_unlock(&thread->args->print);
	usleep(100);
	mutex_destroy(thread);
}

static void	check_death(t_philosopher *thread, int *death, int *eating)
{
	pthread_mutex_lock(&thread->args->data);
	*death = thread->death;
	if (thread->eating == 0)
	{
		(*eating)++;
		thread->eating = -1;
	}
	pthread_mutex_unlock(&thread->args->data);
}

int	main_loop(t_philosopher *thread)
{
	int			death;
	int			eating;
	int			philo;

	philo = thread->args->nop;
	if (create_mutex(thread))
		return (1);
	thread->args->start_time = ft_gettime();
	if (create_thread(thread))
		return (1);
	death = 0;
	eating = 0;
	usleep(1000);
	while (1)
	{
		check_death(thread, &death, &eating);
		if (death == 1 || eating == philo)
		{
			if_death(thread, death);
			break ;
		}
		thread = thread->next;
		usleep(100);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philosopher	*thread;
	t_args			*args;

	args = (t_args *)malloc(sizeof(t_args));
	if (args == NULL)
		return (1);
	thread = NULL;
	if (argc != 5 && argc != 6)
		return (1);
	else
		if (parser(args, argv + 1))
			return (free_error(thread, args));
	if (init_lst(&thread, &args))
		return (free_error(thread, args));
	if (main_loop(thread))
		return (free_error(thread, args));
	ft_lstclear(&thread, free);
	free(args);
	return (0);
}

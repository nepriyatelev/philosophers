/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:19:48 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/22 19:22:27 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*time*/
long long unsigned ft_time(t_philosopher *thread)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	thread->args->time_in_process = (((tv.tv_usec) / 1000) + (tv.tv_sec * 1000));
	return(thread->args->time_in_process);
}

void ft_sleep(t_philosopher *thread, int time)
{
	long long unsigned c = ft_time(thread) - thread->args->start_time + time;
	while((ft_time(thread) - thread->args->start_time) <= c)
		;
	thread->args->start_time += 1;
}
/*end time*/
void *execution(void *incoming_thread)
{
	t_philosopher	*thread;

	thread = (t_philosopher *)incoming_thread;
		thread->args->start_time = ft_time(thread);
	while (1)
	{
		pthread_mutex_lock(&thread->fork);
		pthread_mutex_lock(&thread->args->print);
		printf("%llu ms : philosopher %d has taken a fork %d\n", ft_time(thread) - thread->args->start_time, thread->thread_id, thread->thread_id);
		pthread_mutex_unlock(&thread->args->print);
		pthread_mutex_unlock(&thread->fork);
		pthread_mutex_lock(&thread->fork);
		pthread_mutex_lock(&thread->args->print);
		printf("%llu ms : philosopher %d has taken a fork %d\n", ft_time(thread) - thread->args->start_time, thread->thread_id, thread->next->thread_id);
		pthread_mutex_unlock(&thread->args->print);
		pthread_mutex_unlock(&thread->fork);
		pthread_mutex_lock(&thread->args->print);
		printf("%llu ms : philosopher %d is eating\n", ft_time(thread) - thread->args->start_time, thread->thread_id);
		ft_sleep(thread, thread->args->tte);
		pthread_mutex_unlock(&thread->args->print);
		pthread_mutex_lock(&thread->args->print);
		printf("%llu ms : philosopher %d is sleeping\n", ft_time(thread) - thread->args->start_time, thread->thread_id);
		ft_sleep(thread, thread->args->tts);
		pthread_mutex_unlock(&thread->args->print);
	}
	return (NULL);
}

int	create_thread(t_philosopher	*thread)
{
	int				i;

	i = 0;
	pthread_mutex_init(&thread->args->print, NULL); //create mut
	while (i < thread->args->nop)
	{
		if (pthread_mutex_init(&thread->fork, NULL))
			return (1);
		thread = thread->next;
		i++;
	}
	i = 0;
	while (i < thread->args->nop) //create threads
	{
		if (pthread_create(&thread->thread, NULL, execution, (void *)thread))
			return (1);
		thread = thread->next;
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < thread->args->nop)
	{
		if (pthread_create(&thread->thread, NULL, execution, (void *)thread))
			return (1);
		thread = thread->next;
		i += 2;
	}
	i = 0;
	while (i < thread->args->nop) //join threads
	{
		if (pthread_join(thread->thread, NULL))
			return (1);
		thread = thread->next;
		i++;
	}
	i = 0;
	while (i < thread->args->nop) //destroy mut
	{
		if (pthread_mutex_destroy(&thread->fork))
			return (1);
		thread = thread->next;
		i++;
	}
	if (pthread_mutex_destroy(&thread->args->print))
			return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philosopher	*thread;

	thread = NULL;
	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	else
		if (parser(&thread, argv + 1))
			return (1);
	create_thread(thread);
	return (EXIT_SUCCESS);
}

	// int i = 0;
	// while (i < thread->args->nop)
	// {
	// 	printf("id = %d\tnotemp = %d\t nop = %d\tis dead = %d\ttime = %lld\n", thread->thread_id, thread->args->notepme, thread->args->nop, thread->is_dead, thread->args->start_time);
	// 	thread = thread->next;
	// 	i++;
	// }
	// printf("id = %d\tnotemp = %d\t nop = %d\tis dead = %d\ttime = %lld\n", thread->thread_id, thread->args->notepme, thread->args->nop, thread->is_dead, thread->args->start_time);
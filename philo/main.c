/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:19:48 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/25 19:48:19 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*time*/
long long unsigned ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return(tv.tv_usec / 1000 + tv.tv_sec * 1000);
}

void ft_sleep(t_philosopher *thread, int time)
{
	(void)thread;
	long long unsigned c = ft_time() + time;
	while(ft_time() < c)
		usleep(100);
}
/*end time*/
void *execution(void *incoming_thread)
{
	t_philosopher	*thread;

	thread = (t_philosopher *)incoming_thread;
	// if (thread->thread_id % 2 == 0)
	// 	usleep(100);
	while (thread->full && 1)
	{
		pthread_mutex_lock(&thread->fork);

		pthread_mutex_lock(&thread->args->print);
		printf("%llu ms : philosopher %d has taken a fork %d\n", ft_time() - thread->args->start_time, thread->thread_id, thread->thread_id);
		pthread_mutex_unlock(&thread->args->print);
		
		pthread_mutex_lock(&thread->next->fork);
		
		pthread_mutex_lock(&thread->args->print);
		printf("%llu ms : philosopher %d has taken a fork %d\n", ft_time() - thread->args->start_time, thread->thread_id, thread->next->thread_id);
		pthread_mutex_unlock(&thread->args->print);
		
		pthread_mutex_lock(&thread->args->print);
		printf("%llu ms : philosopher %d is eating\n", ft_time() - thread->args->start_time, thread->thread_id);
		thread->last_eat = ft_time() - thread->args->start_time;
		if (thread->count_eat > 0)
			thread->count_eat--;
		if (thread->count_eat == 0) //добавил для гонки данных
			thread->full++;
		pthread_mutex_unlock(&thread->args->print);
		ft_sleep(thread, thread->args->tte);
		
		pthread_mutex_unlock(&thread->fork);
		
		pthread_mutex_unlock(&thread->next->fork);

		pthread_mutex_lock(&thread->args->print);
		printf("%llu ms : philosopher %d is sleeping\n", ft_time() - thread->args->start_time, thread->thread_id);
		pthread_mutex_unlock(&thread->args->print);
		ft_sleep(thread, thread->args->tts); //возмозможно на 67, а возмоэно тут

		pthread_mutex_lock(&thread->args->print);
		printf("%llu ms : philosopher %d is thinking\n", ft_time() - thread->args->start_time, thread->thread_id);
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
	thread->args->start_time = ft_time();
	i = 0;
	while (i < thread->args->nop) //create threads
	{
		thread->last_eat = ft_time() - thread->args->start_time;
		if (pthread_create(&thread->thread, NULL, execution, (void *)thread))
			return (1);
		thread = thread->next;
		i++;
		usleep(100);
	}
	// if (thread->args->notepme > 0)
	// {
	// 	i = 0;
	// 	while (i < thread->args->nop) //join threads
	// 	{
	// 		if (pthread_join(thread->thread, NULL))
	// 			return (1);
	// 		thread = thread->next;
	// 		i++;
	// 	}
	// 	i = 0;
	// while (i < thread->args->nop) //destroy mut
	// {
	// 	if (pthread_mutex_destroy(&thread->fork))
	// 		return (1);
	// 	thread = thread->next;
	// 	i++;
	// }
	// if (pthread_mutex_destroy(&thread->args->print))
	// 		return (1);
	// }
	// else
	// {
		while (1)
		{
			if (thread->full == 0 && thread->args->nop != 1)
			{
				i = 0;
				while (i < thread->args->nop) //join threads
				{
					if (pthread_join(thread->thread, NULL))
						return (1);
					thread = thread->next;
					i++;
				}
				usleep(1000);
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
			}
			else if ((int)(ft_time() - thread->args->start_time - thread->last_eat) >= thread->args->ttd)
			{
				i = 0;
				pthread_mutex_lock(&thread->args->print);
				printf("%llu ms : philosopher %d is death\n", ft_time() - thread->args->start_time, thread->thread_id);
				while (i < thread->args->nop) //join threads
				{
					if (pthread_detach(thread->thread))
						return (1);
					thread = thread->next;
					i++;
				}
				usleep(1000);
				i = 0;
				while (i < thread->args->nop) //destroy mut
				{
					if (pthread_mutex_destroy(&thread->fork))
						return (1);
					thread = thread->next;
					i++;
				}
				pthread_mutex_unlock(&thread->args->print);
				if (pthread_mutex_destroy(&thread->args->print))
					return (1);
			}
			thread = thread->next;
		}
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
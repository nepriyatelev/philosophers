/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:19:48 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/27 21:24:43 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *execution(void *incoming_thread)
{
	t_philosopher	*thread;

	thread = (t_philosopher *)incoming_thread;
	while (1)
	{
		pthread_mutex_lock(&thread->fork);
		pthread_mutex_lock(&thread->args->print);
		printf("%llu ms : philosopher %d has taken a fork %d\n", ft_gettime() - thread->args->start_time, thread->thread_id, thread->thread_id);
		pthread_mutex_unlock(&thread->args->print);
		
		pthread_mutex_lock(&thread->next->fork);
		pthread_mutex_lock(&thread->args->print);
		printf("%llu ms : philosopher %d has taken a fork %d\n", ft_gettime() - thread->args->start_time, thread->thread_id, thread->next->thread_id);
		pthread_mutex_unlock(&thread->args->print);
		
		pthread_mutex_lock(&thread->args->print);
		printf("%llu ms : philosopher %d is eating\n", ft_gettime() - thread->args->start_time, thread->thread_id);
		pthread_mutex_lock(&thread->args->data);
		if (((ft_gettime() - thread->args->start_time - thread->last_eat) >= (long long)thread->args->ttd) && thread->death == 0)
			thread->death = 1;
		thread->last_eat = ft_gettime() - thread->args->start_time;
		if (thread->eating > 0)
			thread->eating--;
		pthread_mutex_unlock(&thread->args->data);
		pthread_mutex_unlock(&thread->args->print);
		ft_sleep(thread->args->tte);
		
		pthread_mutex_unlock(&thread->fork);
		pthread_mutex_unlock(&thread->next->fork);
		

		pthread_mutex_lock(&thread->args->print);
		printf("%llu ms : philosopher %d is sleeping\n", ft_gettime() - thread->args->start_time, thread->thread_id);
		pthread_mutex_unlock(&thread->args->print);
		ft_sleep(thread->args->tts); //возмозможно на 67, а возмоэно тут

		pthread_mutex_lock(&thread->args->print);
		printf("%llu ms : philosopher %d is thinking\n", ft_gettime() - thread->args->start_time, thread->thread_id);
		pthread_mutex_unlock(&thread->args->print);
	}
	return (NULL);
}

int	create_mutex(t_philosopher	*thread) //еще можно добавить мутекс на ошибки
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&thread->args->print, NULL))
		return (ERROR_MUTEX_INIT);
	if (pthread_mutex_init(&thread->args->data, NULL))
		return (ERROR_MUTEX_INIT);
	while (i < thread->args->nop)
	{
		if (pthread_mutex_init(&thread->fork, NULL))
			return (ERROR_MUTEX_INIT);
		thread = thread->next;
		i++;
	}
	return (0);
}

int	create_thread(t_philosopher	*thread)
{
	int	i;

	i = 0;
	while (i < thread->args->nop)
	{
		if (pthread_create(&thread->thread, NULL, execution, (void *)thread))
			return (ERROR_THREAD_CREATE);
		thread = thread->next;
		i++;
		usleep(100);
	}
	return (0);
}

int	thread_detatch(t_philosopher	*thread)
{
	int	i;

	i = 0;
	while (i < thread->args->nop)
	{
		if (pthread_detach(thread->thread))
			return (ERROR_THREAD_DETACH);
		thread = thread->next;
		i++;
	}
	return (0);
}

int	mutex_destroy(t_philosopher	*thread)
{
	int	i;

	i = 0;
	while (i < thread->args->nop)
	{
		if (pthread_mutex_destroy(&thread->fork))
			return (ERROR_MUTEX_DESTROY);
		thread = thread->next;
		i++;
	}
	if (pthread_mutex_destroy(&thread->args->print))
		return (ERROR_MUTEX_DESTROY);
	if (pthread_mutex_destroy(&thread->args->data))
		return (ERROR_MUTEX_DESTROY);
	return (0);
}

// int	thread_join(t_philosopher	*thread)
// {
// 	int	i;

// 	i = 0;
// 	while (i < thread->args->nop)
// 	{
// 		if (pthread_join(thread->thread, NULL))
// 			return (ERROR_THREAD_JOIN);
// 		thread = thread->next;
// 		i++;
// 	}
// 	return (0);
// }

int	loop(t_philosopher *thread)
{
	long long	time_to_print;
	int			death;
	int			eating;
	int			philo;

	pthread_mutex_lock(&thread->args->data);
	philo = thread->args->nop;
	pthread_mutex_unlock(&thread->args->data);
	death = 0;
	eating = 0;
	time_to_print = 0;
	usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&thread->args->data);
		death = thread->death;
		pthread_mutex_unlock(&thread->args->data);
		if (death == 1)
		{
			pthread_mutex_lock(&thread->args->print);
			pthread_mutex_lock(&thread->args->data);
			time_to_print = ft_gettime();
			if (time_to_print < 0)
				return (ERROR_GETTIMEOFDAY);
			else
				time_to_print -= thread->args->start_time;
			printf("%llu ms : philosopher %d is death\n", time_to_print, thread->thread_id);
			thread_detatch(thread);
			pthread_mutex_unlock(&thread->args->data);
			pthread_mutex_unlock(&thread->args->print);
			mutex_destroy(thread);
			break ;
		}
		pthread_mutex_lock(&thread->args->data);
		if (thread->eating == 0)
		{
			eating++;
			thread->eating = -1;
		}
		pthread_mutex_unlock(&thread->args->data);
		if (eating == philo && philo != 1)
		{
			thread_detatch(thread);
			mutex_destroy(thread);
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
	int				status;

	status = 0;
	args = (t_args *)malloc(sizeof(t_args));
	if (args == NULL)
		return (ERROR_ALLOCATION);
	thread = NULL;
	if (argc != 5 && argc != 6)
		return (ERROR_INPUT);
	else
		if (parser(args, argv + 1))
			return (ERROR_INPUT);
	if (init_lst(&thread, &args))
		return (ERROR_ALLOCATION);
	if (create_mutex(thread))
		return (ERROR_MUTEX_INIT);
	thread->args->start_time = ft_gettime();
	if (thread->args->start_time < 0)
		return (ERROR_GETTIMEOFDAY);
	create_thread(thread);
	status = loop(thread);
	if (status)
		return (status);
	return (EXIT_SUCCESS);
}
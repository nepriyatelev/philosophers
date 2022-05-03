/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:26:22 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/29 19:14:14 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_your_fork(t_philosopher *thread, long long time_to_print)
{
	pthread_mutex_lock(&thread->fork);
	pthread_mutex_lock(&thread->args->print);
	pthread_mutex_lock(&thread->args->data);
	time_to_print = ft_gettime() - thread->args->start_time;
	printf("%llu ms : philosopher %d has taken a fork %d\n", \
		time_to_print, thread->thread_id, thread->thread_id);
	pthread_mutex_unlock(&thread->args->data);
	pthread_mutex_unlock(&thread->args->print);
}

void	starts_eating(t_philosopher *thread, long long time_to_print)
{
	pthread_mutex_lock(&thread->next->fork);
	pthread_mutex_lock(&thread->args->print);
	pthread_mutex_lock(&thread->args->data);
	time_to_print = ft_gettime() - thread->args->start_time;
	printf("%llu ms : philosopher %d has taken a fork %d\n", \
		time_to_print, thread->thread_id, thread->next->thread_id);
	printf("%llu ms : philosopher %d is eating\n", \
		time_to_print, thread->thread_id);
	if (thread->eating > 0)
		thread->eating--;
	pthread_mutex_unlock(&thread->args->data);
	pthread_mutex_unlock(&thread->args->print);
}

void	starts_to_sleep(t_philosopher *thread, long long time_to_print)
{
	pthread_mutex_lock(&thread->args->print);
	pthread_mutex_lock(&thread->args->data);
	time_to_print = ft_gettime() - thread->args->start_time;
	printf("%llu ms : philosopher %d is sleeping\n", \
		time_to_print, thread->thread_id);
	pthread_mutex_unlock(&thread->args->data);
	pthread_mutex_unlock(&thread->args->print);
	ft_sleep(thread->args->tts);
}

void	begins_to_think(t_philosopher *thread, long long time_to_print)
{
	pthread_mutex_lock(&thread->args->print);
	pthread_mutex_lock(&thread->args->data);
	time_to_print = ft_gettime() - thread->args->start_time;
	printf("%llu ms : philosopher %d is thinking\n", \
		time_to_print, thread->thread_id);
	pthread_mutex_unlock(&thread->args->data);
	pthread_mutex_unlock(&thread->args->print);
}

void	checking_the_status(t_philosopher *thread, long long check_time)
{
	pthread_mutex_lock(&thread->args->data);
	check_time = ft_gettime() - thread->args->start_time - thread->last_eat;
	if ((check_time >= (long long)thread->args->ttd) && thread->death == 0)
		thread->death = 1;
	thread->last_eat = ft_gettime() - thread->args->start_time;
	pthread_mutex_unlock(&thread->args->data);
}

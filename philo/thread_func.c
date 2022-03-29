/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:31:43 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/29 17:03:40 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mutex_destroy(t_philosopher	*thread)
{
	int	i;

	i = 0;
	while (i < thread->args->nop)
	{
		if (pthread_mutex_destroy(&thread->fork))
			return (1);
		thread = thread->next;
		i++;
	}
	if (pthread_mutex_destroy(&thread->args->print))
		return (1);
	if (pthread_mutex_destroy(&thread->args->data))
		return (1);
	return (0);
}

int	thread_detatch(t_philosopher	*thread)
{
	int	i;

	i = 0;
	while (i < thread->args->nop)
	{
		if (pthread_detach(thread->thread))
			return (1);
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
			return (1);
		thread = thread->next;
		i++;
		usleep(100);
	}
	return (0);
}

int	create_mutex(t_philosopher	*thread)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&thread->args->print, NULL))
		return (1);
	if (pthread_mutex_init(&thread->args->data, NULL))
		return (1);
	while (i < thread->args->nop)
	{
		if (pthread_mutex_init(&thread->fork, NULL))
			return (1);
		thread = thread->next;
		i++;
	}
	return (0);
}

int	thread_join(t_philosopher	*thread)
{
	int	i;

	i = 0;
	while (i < thread->args->nop)
	{
		if (pthread_join(thread->thread, NULL))
			return (1);
		thread = thread->next;
		i++;
	}
	return (0);
}
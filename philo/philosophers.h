/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:19:45 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/25 19:41:45 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_args
{
	int					nop;		/*number_of_philosophers*/
	int					ttd;		/*time_to_die*/
	int					tte;		/*time_to_eat*/
	int					tts;		/*time_to_sleep*/
	int					notepme;	/*number_of_times_each_philosopher_must_eat*/
	pthread_mutex_t		print;
	unsigned long long	start_time;
	unsigned long long	process_time;
	// unsigned long long	time_in_process;
}	t_args;

typedef struct s_philosopher
{
	pthread_t				thread;
	pthread_mutex_t			fork;
	t_args					*args;
	int						thread_id;
	int						count_eat;
	int						full;
	long long unsigned		last_eat;
	long long unsigned		ttd;
	struct s_philosopher	*next;
}	t_philosopher;

int	ft_atoi(const char *str);
int	ft_isdigit(int c);
void	ft_lstadd_back(t_philosopher **lst, t_philosopher *new);
t_philosopher	*ft_lstlast(t_philosopher *lst);
t_philosopher	*ft_lstnew(t_args **args, int id);

int	parser(t_philosopher **thread, char **input);


#endif
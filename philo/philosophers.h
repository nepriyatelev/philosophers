/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:19:45 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/27 21:00:27 by modysseu         ###   ########.fr       */
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

# define ERROR_ALLOCATION		-1
# define ERROR_INPUT			-2
# define ERROR_GETTIMEOFDAY		-3
# define ERROR_MUTEX_INIT		-4
# define ERROR_THREAD_CREATE	-5
# define ERROR_THREAD_DETACH	-6
# define ERROR_MUTEX_DESTROY	-7
# define ERROR_THREAD_JOIN		-8
# define ERROR_MUTEX_LOCK		-9
# define ERROR_MUTEX_UNLOCK		-10

typedef struct s_args
{
	int					nop;		/*number_of_philosophers*/
	int					ttd;		/*time_to_die*/
	int					tte;		/*time_to_eat*/
	int					tts;		/*time_to_sleep*/
	int					notepme;	/*number_of_times_each_philosopher_must_eat*/
	pthread_mutex_t		print;
	pthread_mutex_t		data;
	long long			start_time;
}	t_args;

typedef struct s_philosopher
{
	pthread_t				thread;
	pthread_mutex_t			fork;
	t_args					*args;
	int						thread_id;
	int						death;
	int						eating;
	long long				last_eat;
	struct s_philosopher	*next;
}	t_philosopher;

int				ft_atoi(const char *str);
int				ft_isdigit(int c);
long long		ft_gettime(void);
int				ft_sleep(int time);

void			ft_lstadd_back(t_philosopher **lst, t_philosopher *new);
t_philosopher	*ft_lstlast(t_philosopher *lst);
t_philosopher	*ft_lstnew(t_args **args, int id);
void			ft_lstclear(t_philosopher **lst, void (*del)(void*));

int				parser(t_args *args, char **input);
int				init_lst(t_philosopher **thread, t_args **args);


#endif
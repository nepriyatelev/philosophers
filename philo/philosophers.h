/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:19:45 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/29 19:13:57 by modysseu         ###   ########.fr       */
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
void			ft_sleep(int time);
int				free_error(t_philosopher *thread, t_args *args);

void			ft_lstadd_back(t_philosopher **lst, t_philosopher *new);
t_philosopher	*ft_lstlast(t_philosopher *lst);
t_philosopher	*ft_lstnew(t_args **args, int id);
void			ft_lstclear(t_philosopher **lst, void (*del)(void*));

int				parser(t_args *args, char **input);
int				init_lst(t_philosopher **thread, t_args **args);

int				mutex_destroy(t_philosopher	*thread);
int				thread_detatch(t_philosopher	*thread);
int				create_thread(t_philosopher	*thread);
int				create_mutex(t_philosopher	*thread);
int				thread_join(t_philosopher	*thread);
void			*execution(void *incoming_thread);
void			take_your_fork(t_philosopher *thread, long long time_to_print);
void			starts_eating(t_philosopher *thread, long long time_to_print);
void			starts_to_sleep(t_philosopher *thread, long long time_to_print);
void			begins_to_think(t_philosopher *thread, long long time_to_print);
void			checking_the_status(t_philosopher *thread,
						long long check_time);

#endif
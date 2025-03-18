/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmixtur <fmixtur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:30:10 by fmixtur           #+#    #+#             */
/*   Updated: 2025/03/18 13:30:10 by fmixtur          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	long			start_time;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
	long			last_meal;
	int				meals_eaten;
	int				is_dead;
}	t_philo;

typedef struct s_monitor
{
	pthread_t		thread;
	pthread_mutex_t	*mutex;
	t_philo			*philo;
	t_data			*data;
}	t_monitor;

void	set_all(t_philo **philo, t_data *data, t_monitor *monitor, char **argv);
int		ft_atoi(const char *str);
void	cleanup(t_philo *philo);
void	*philo_cycle(void *arg);
long	get_time(void);
void	philo_pick_forks(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	*monitor_cycle(void *arg);
#endif

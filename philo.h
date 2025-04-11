/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmixtur <fmixtur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 02:11:20 by fmixtur           #+#    #+#             */
/*   Updated: 2025/04/11 02:11:20 by fmixtur          ###   ########.ch       */
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
	int				is_full;
	int				end;
}	t_philo;

typedef struct s_monitor
{
	pthread_t		thread;
	t_philo			*philo;
	t_data			*data;
}	t_monitor;

int		set_all(t_philo **philo, t_data *data, t_monitor *monitor, char **argv);
int		ft_atoi(const char *str);

int		cleanup(t_philo *philo);
void	*philo_cycle(void *arg);
int		ft_strcmp(const char *s1, const char *s2);
long	get_time(void);
int		philo_pick_forks(t_philo *philo);
void	philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		philo_think(t_philo *philo);
void	*monitor_cycle(void *arg);
int		stop_check(t_philo *philo);
void	print_philo_action(t_philo *philo, char *status, char *color);
int		is_valid_number(char *str);
#endif

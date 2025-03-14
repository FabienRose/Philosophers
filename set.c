/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmixtur <fmixtur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:22:06 by fmixtur           #+#    #+#             */
/*   Updated: 2025/03/14 12:22:06 by fmixtur          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


long	get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}
void	set_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
}

void	set_philo(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].data = data;
		(*philo)[i].last_meal = 0;
		(*philo)[i].meals_eaten = 0;
		(*philo)[i].is_dead = 0;
		(*philo)[i].left_fork = &data->forks[i];
		(*philo)[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		i++;
	}
}

void	set_all(t_philo **philo, t_data *data, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return ;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	set_forks(data);
	*philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!*philo)
	{
		free(data->forks);
		return ;
	}
	set_philo(philo, data);
	data->start_time = get_time();
	data->someone_died = 0;
}
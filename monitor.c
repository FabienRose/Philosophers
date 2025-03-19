/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmixtur <fmixtur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:23:40 by fmixtur           #+#    #+#             */
/*   Updated: 2025/03/19 09:30:04 by fmixtur          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_full(t_monitor *monitor)
{
	int	i;
	int	all_full;

	if (monitor->data->nb_eat == -1)
		return (0);
	i = 0;
	all_full = 1;
	while (i < monitor->data->nb_philo)
	{
		if (monitor->philo[i].meals_eaten < monitor->data->nb_eat)
		{
			all_full = 0;
			break ;
		}
		i++;
	}
	return (all_full);
}

void	*monitor_cycle(void *arg)
{
	t_monitor	*monitor;
	int			i;
	long		current_time;

	monitor = (t_monitor *)arg;
	while (1)
	{
		if (check_all_full(monitor))
		{
			pthread_mutex_lock(&monitor->data->death_mutex);
			monitor->data->someone_died = 1;
			pthread_mutex_unlock(&monitor->data->death_mutex);
			pthread_mutex_lock(&monitor->data->print_mutex);
			printf("All philosophers have eaten enough times!\n");
			pthread_mutex_unlock(&monitor->data->print_mutex);
			return (NULL);
		}
		i = 0;
		while (i < monitor->data->nb_philo)
		{
			current_time = get_time();
			if (current_time - monitor->philo[i].last_meal
				> monitor->data->time_to_die)
			{
				pthread_mutex_lock(&monitor->data->death_mutex);
				monitor->data->someone_died = 1;
				pthread_mutex_unlock(&monitor->data->death_mutex);
				pthread_mutex_lock(&monitor->data->print_mutex);
				printf("%ld %d died\n", get_time() - monitor->data->start_time, 
					monitor->philo[i].id);
				pthread_mutex_unlock(&monitor->data->print_mutex);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
}

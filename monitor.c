/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmixtur <fmixtur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:44:45 by fmixtur           #+#    #+#             */
/*   Updated: 2025/04/04 17:49:31 by fmixtur          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_full(t_monitor *monitor)
{
	int	i;
	int	all_full;

	if (monitor->data->nb_eat == -1)
		return (0);
	i = -1;
	all_full = TRUE;
	while (++i < monitor->data->nb_philo)
	{
		if (monitor->philo[i].is_full == 0)
		{
			all_full = FALSE;
			break ;
		}
	}
	if (all_full)
	{
		pthread_mutex_lock(&monitor->data->print_mutex);
		pthread_mutex_lock(&monitor->data->death_mutex);
		monitor->data->someone_died = TRUE;
		pthread_mutex_unlock(&monitor->data->death_mutex);
		printf("\033[1;32mAll philosophers have eaten enough times!\033[0m\n");
		pthread_mutex_unlock(&monitor->data->print_mutex);
	}
	return (all_full);
}

int	philo_finished(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->data->nb_philo)
	{
		if (monitor->philo[i].end == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	death_checker(t_monitor *monitor)
{
	int		i;
	long	current_time;

	i = 0;
	while (i < monitor->data->nb_philo)
	{
		current_time = get_time();
		if ((current_time - monitor->philo[i].last_meal
				> monitor->data->time_to_die)
			&& monitor->philo[i].is_full == 0)
		{
			pthread_mutex_lock(&monitor->data->death_mutex);
			monitor->data->someone_died = 1;
			pthread_mutex_unlock(&monitor->data->death_mutex);
			pthread_mutex_lock(&monitor->data->print_mutex);
			printf("\033[1;31m%ld %d died\033[0m\n",
				get_time() - monitor->data->start_time,
				monitor->philo[i].id);
			pthread_mutex_unlock(&monitor->data->print_mutex);
			break ;
		}
		i++;
	}
	return (0);
}

void	*monitor_cycle(void *arg)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)arg;
	while (1)
	{
		if (check_all_full(monitor))
			break ;
		death_checker(monitor);
		if (monitor->data->someone_died)
			break ;
		usleep(1000);
	}
	while (!philo_finished(monitor))
		usleep(1000);
	cleanup(monitor->philo);
	return (NULL);
}

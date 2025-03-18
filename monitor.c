/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmixtur <fmixtur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:30:47 by fmixtur           #+#    #+#             */
/*   Updated: 2025/03/18 13:31:15 by fmixtur          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_cycle(void *arg)
{
	t_monitor	*monitor;
	int			i;

	monitor = (t_monitor *)arg;
	while (1)
	{
		i = 0;
		while (i < monitor->data->nb_philo)
		{
			if (get_time() - monitor->philo[i].last_meal > monitor->data->time_to_die)
			{
				pthread_mutex_lock(&monitor->data->print_mutex);
				printf("%ld %d died\n", get_time() - monitor->data->start_time, monitor->philo[i].id);
				printf("DEBUG : %ld\n", (monitor->philo[i].last_meal - get_time()));
				pthread_mutex_destroy(&monitor->data->print_mutex);
				return (NULL);
			}
			i++;
		}

	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmixtur <fmixtur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:50:04 by fmixtur           #+#    #+#             */
/*   Updated: 2025/04/03 15:52:11 by fmixtur          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		pthread_mutex_destroy(&philo->data->forks[i]);
		i++;
	}
	free(philo->data->forks);
}

void	destroy_mutexes(t_philo *philo)
{
	pthread_mutex_destroy(&philo->data->print_mutex);
	pthread_mutex_destroy(&philo->data->death_mutex);
	destroy_forks(philo);
}

int	cleanup(t_philo *philo)
{
	destroy_mutexes(philo);
	free(philo);
	return (0);
}

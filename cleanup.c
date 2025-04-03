/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmixtur <fmixtur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:24:41 by fmixtur           #+#    #+#             */
/*   Updated: 2025/04/03 12:09:03 by fmixtur          ###   ########.ch       */
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

void	cleanup(t_philo *philo)
{
	destroy_mutexes(philo);
	free(philo);
}

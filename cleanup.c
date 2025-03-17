/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmixtur <fmixtur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:38:02 by fmixtur           #+#    #+#             */
/*   Updated: 2025/03/16 18:39:01 by fmixtur          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	destroy_mutexes(t_philo *philo)
{
	pthread_mutex_destroy(&philo->data->print_mutex);
	pthread_mutex_destroy(&philo->data->death_mutex);
}

void	cleanup(t_philo *philo)
{
	destroy_mutexes(philo);
	free(philo);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmixtur <fmixtur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 09/04/2025 10:00:47 by fmixtur           #+#    #+#             */
/*   Updated: 09/04/2025 10:00:47 by fmixtur          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stop_check(t_philo *philo)
{
	int	status;

	status = FALSE;
	if (philo->data->nb_eat != -1 && (philo->meals_eaten
			>= philo->data->nb_eat))
	{
		philo->is_full = TRUE;
		status = TRUE;
	}
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died)
		status = TRUE;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (status);
}

void	print_philo_action(t_philo *philo, char *action, char *color)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (stop_check(philo) && ft_strcmp(action, "is eating") != 0)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	printf("\033[1;35m%ld %d\033[0m %s%s\033[0m\n",
		get_time() - philo->data->start_time, philo->id, color, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmixtur <fmixtur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:44:38 by fmixtur           #+#    #+#             */
/*   Updated: 2025/03/17 10:49:42 by fmixtur          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_cycle(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	while (TRUE)
	{
		philo_pick_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("At %ld, philo %d is thinking\n",
			get_time() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}

	return (NULL);
}

void	philo_pick_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(first_fork);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("At %ld, philo %d has taken a fork\n",
		get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_lock(second_fork);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("At %ld, philo %d has taken a fork\n",
		get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("At %ld, philo %d is eating\n",
		get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("At %ld, philo %d is sleeping\n",
		get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->time_to_sleep * 1000);
}

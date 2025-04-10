/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmixtur <fmixtur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:11:27 by fmixtur           #+#    #+#             */
/*   Updated: 2025/04/09 10:13:23 by fmixtur          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_cycle(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat / 3 * 1000);
	else if (philo->data->nb_philo % 2 == 1)
		usleep(philo->data->time_to_eat / 2 * 1000);
	while (TRUE)
	{
		if (stop_check(philo))
			break ;
		if (!philo_pick_forks(philo))
			break ;
		if (stop_check(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		philo_eat(philo);
		if (stop_check(philo))
			break ;
		philo_sleep(philo);
		if (stop_check(philo))
			break ;
		philo_think(philo);
	}
	philo->end = TRUE;
	return (NULL);
}

int	philo_pick_forks(t_philo *philo)
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
	if (stop_check(philo))
	{
		pthread_mutex_unlock(first_fork);
		return (FALSE);
	}
	print_philo_action(philo, "has taken a fork", "\033[36m");
	if (philo->data->nb_philo < 2)
		return (FALSE);
	if (stop_check(philo))
	{
		pthread_mutex_unlock(first_fork);
		return (FALSE);
	}
	pthread_mutex_lock(second_fork);
	print_philo_action(philo, "has taken a fork", "\033[36m");
	return (TRUE);
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
	print_philo_action(philo, "is eating", "\033[38;5;208m");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_philo_action(philo, "is sleeping", "\033[33m");
	usleep(philo->data->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	int	thinking_time;

	print_philo_action(philo, "is thinking", "\033[34m");
	thinking_time = philo->data->time_to_die / 5;
	if ((thinking_time + philo->data->time_to_eat + philo->data->time_to_sleep)
		>= philo->data->time_to_die)
		thinking_time = (philo->data->time_to_die - philo->data->time_to_eat
				- philo->data->time_to_sleep) / 2;
	if (philo->data->nb_philo % 2 == 1)
	{
		if (philo->id == 1)
			thinking_time = philo->data->time_to_eat / 2;
		else if (philo->id % 2 == 0)
			thinking_time = thinking_time / 2;
		else
			thinking_time = thinking_time * 2 / 3;
	}
	if (thinking_time > philo->data->time_to_die / 3)
		thinking_time = philo->data->time_to_die / 3;
	usleep(thinking_time * 1000);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmixtur <fmixtur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:52:38 by fmixtur           #+#    #+#             */
/*   Updated: 2025/04/03 11:53:43 by fmixtur          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stop_check(t_philo *philo)
{
	int	status;

	status = FALSE;
	if (philo->data->nb_eat != -1 && philo->meals_eaten >= philo->data->nb_eat)
	{
		philo->is_full = TRUE;
		status = TRUE;
	}
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died)
		status = TRUE ;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (status);
}
void	*philo_cycle(void *arg)
{
	t_philo			*philo;
	int				thinking_time;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat / 3 * 1000);
	else if (philo->data->nb_philo % 2 == 1)
		usleep(philo->data->time_to_eat / 2 * 1000);
	while (TRUE)
	{
		if (stop_check(philo))
			break ;
		philo_pick_forks(philo);
		philo_eat(philo);
		if (stop_check(philo))
			break ;
		philo_sleep(philo);
		if (stop_check(philo))
			break ;
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d is thinking\n",
			get_time() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		thinking_time = philo->data->time_to_die / 5;
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
	printf("philo %d FINISHED EATING\n", philo->id);
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
	printf("%ld %d has taken a fork\n",
		get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_lock(second_fork);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d has taken a fork\n",
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
	printf("%ld %d is eating\n",
		get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
	printf("%ld %d is sleeping\n",
		get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->time_to_sleep * 1000);
}

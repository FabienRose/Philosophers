/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmixtur <fmixtur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:11:07 by fmixtur           #+#    #+#             */
/*   Updated: 2025/03/14 15:33:54 by fmixtur          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_eat(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    while (1)
    {
        // Determine which fork to take first based on ID
        if (philo->id % 2 == 0)  // Even numbered philosophers
        {
            first_fork = philo->left_fork;
            second_fork = philo->right_fork;
        }
        else  // Odd numbered philosophers
        {
            first_fork = philo->right_fork;
            second_fork = philo->left_fork;
        }

        // Take first fork
        pthread_mutex_lock(first_fork);
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("At %ld, philo %d has taken a fork\n", get_time() - philo->data->start_time, philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);

        // Take second fork
        pthread_mutex_lock(second_fork);
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("At %ld, philo %d has taken a fork\n", get_time() - philo->data->start_time, philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);

        // Eat
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("At %ld, philo %d is eating\n", get_time() - philo->data->start_time, philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);
        usleep(philo->data->time_to_eat * 1000);

        // Put down forks
        pthread_mutex_unlock(second_fork);
        pthread_mutex_unlock(first_fork);

        // Sleep
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("At %ld, philo %d is sleeping\n", get_time() - philo->data->start_time, philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);
        usleep(philo->data->time_to_sleep * 1000);

        // Think
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("At %ld, philo %d is thinking\n", get_time() - philo->data->start_time, philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);
    }

    return (NULL);
}
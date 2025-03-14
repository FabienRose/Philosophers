/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmixtur <fmixtur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:45:35 by fmixtur           #+#    #+#             */
/*   Updated: 2025/03/14 15:15:31 by fmixtur          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
    t_data data;
    t_philo *philo;
    int i;

    if (argc < 5 || argc > 6)
    {
        printf("Error: wrong number of arguments\n");
        return (1);
    }
    set_all(&philo, &data, argv);
    i = 0;
    while (i < data.nb_philo)
    {
        pthread_create(&philo[i].thread, NULL, philo_eat, &philo[i]);
        i++;
    }
    i = 0;
    while (i < data.nb_philo)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
    cleanup(philo);
    return (0);
}
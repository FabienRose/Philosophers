/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmixtur <fmixtur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:25:48 by fmixtur           #+#    #+#             */
/*   Updated: 2025/03/19 10:25:48 by fmixtur          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo;
	t_monitor	monitor;
	int			i;

	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (set_all(&philo, &data, &monitor, argv) == TRUE)
		return (1);
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_create(&philo[i].thread, NULL, philo_cycle, &philo[i]);
		i++;
	}
	pthread_create(&monitor.thread, NULL, monitor_cycle, &monitor);
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_detach(philo[i].thread);
		i++;
	}
	pthread_join(monitor.thread, NULL);
	cleanup(philo);
	return (0);
}

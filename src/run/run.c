/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:23:16 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/16 17:45:33 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void	start_routine(t_table *table, t_philo **philo)
{
	int			i;
    pthread_t	monitor_thread;
	t_philo		*philo_array;

	philo_array = *philo;
	i = 0;
	pthread_create(&monitor_thread, NULL, monitor, philo_array);
	while(i < table->number_of_philos)
	{
		pthread_create(&(*philo)[i].thread, NULL, routine, &(*philo)[i]);
		i++;
	}
	i = 0;
	while(i < table->number_of_philos)
	{
		pthread_join((*philo)[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}

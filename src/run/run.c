/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:23:16 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/31 04:39:27 by joschmun         ###   ########.fr       */
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
	while (i < table->number_of_philos)
	{
		pthread_create(&(*philo)[i].thread, NULL, routine, &(*philo)[i]);
		i++;
	}
	i = 0;
	while (i < table->number_of_philos)
	{
		pthread_join((*philo)[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}

int smart_sleep(t_philo *philo, long long time)
{
	long long	start_time;

	start_time = get_time_stamp(philo->table_p->start_time);
	while ((get_time_stamp(philo->table_p->start_time) - start_time) < time)
	{
		if (check_alive(philo))
			return(1);
		usleep(100);
	}
	return(0);
}

int	pickup_right(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex);
	print(philo, "has taken a fork");
	if (check_alive(philo))
		return(1);
	pthread_mutex_lock(&philo->left_fork->mutex);
	print(philo, "has taken a fork");
	return (0);
}

int	pickup_left(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	print(philo, "has taken a fork");
	if (check_alive(philo))
		return(1);
	pthread_mutex_lock(&philo->right_fork->mutex);
	print(philo, "has taken a fork");
	return (0);
}
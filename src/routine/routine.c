/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:17:32 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/31 14:57:39 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"
#include "run.h"
#include <unistd.h>

int	_take_forks(t_philo *philo)
{
	if (check_alive(philo))
		return(1);
	if (philo->id % 2 == 1)
	{
		if (pickup_left(philo))
			return (1);
	}
	else if (philo->id == 0 && philo->table_p->number_of_philos % 2 == 0)
	{
		if (pickup_right(philo))
			return (1);
	}
	else
	{
		if (pickup_right(philo))
			return (1);
	}
	return (0);
}

int	_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_mutex);
	philo->start_dying = get_time_stamp(philo->table_p->start_time);
	pthread_mutex_unlock(&philo->data_mutex);
	print(philo, "is eating");
	if (smart_sleep(philo, philo->table_p->time_to_eat))
	{
		putdown(philo);
        return (1);
	}
	putdown(philo);
	pthread_mutex_lock(&philo->data_mutex);
	philo->meal_count++;
	if (philo->meal_count == philo->table_p->number_of_meals)
	{
		pthread_mutex_unlock(&philo->data_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data_mutex);
	return (0);
}

int	_sleep(t_philo *philo)
{
	if (check_alive(philo))
		return(1);
	print(philo, "is sleeping");
	if (smart_sleep(philo, philo->table_p->time_to_sleep))
		return (1);
	return (0);
}

int	_think(t_philo *philo)
{
	if (check_alive(philo))
		return(1);
	print(philo, "is thinking");
	if (smart_sleep(philo, 3))
		return (1);
	return (0);
}

void	*routine(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	if (philo->id % 2 == 0)
		usleep(100);
	else if (philo->id == 0 && philo->table_p->number_of_philos % 2 != 0)
		usleep(200);
	pthread_mutex_lock(&philo->data_mutex);
	philo->start_dying = get_time_stamp(philo->table_p->start_time);
	pthread_mutex_unlock(&philo->data_mutex);
	while (!check_alive(philo))
	{
		if (routine_split(&philo))
			break ;
	}
	return (NULL);
}

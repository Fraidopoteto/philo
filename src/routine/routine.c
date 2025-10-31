/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:17:32 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/31 04:46:47 by joschmun         ###   ########.fr       */
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
	philo->start_dying = get_time_stamp(philo->table_p->start_time);
	print(philo, "is eating");
	if (smart_sleep(philo, philo->table_p->time_to_eat))
	{
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		return (1);
	}
	if (philo->id % 2 == 0 && philo->id != 0)
	{
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo->right_fork->mutex);
		pthread_mutex_unlock(&philo->left_fork->mutex);
	}
	philo->meal_count++;
	if (philo->meal_count == philo->table_p->number_of_meals)
		return (1);
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
	if (smart_sleep(philo, 10))
		return (1);
	return (0);
}

void	*routine(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	if (philo->table_p->number_of_philos == 1)
	{
		print(philo, "has taken a fork");
		philo->table_p->dead = 1;
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(100);
	else if (philo->id == 0 && philo->table_p->number_of_philos % 2 != 0)
		usleep(200);
	while (!check_alive(philo))
	{
		if (routine_split(&philo))
			break ;
	}
	return (NULL);
}

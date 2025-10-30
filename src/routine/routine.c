/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:17:32 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/30 16:03:13 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"
#include "run.h"
#include <unistd.h>

int	_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->mutex);
		print(philo, "has taken a fork");
	}
	else if (philo->id == 0 && philo->table_p->number_of_philos % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->mutex);
		print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->mutex);
		print(philo, "has taken a fork");
	}
	return (0);
}

int	_eat(t_philo *philo)
{
	if (_take_forks(philo))
	{
		philo->table_p->dead = 1;
		return (1);
	}
	philo->start_dying = get_time_stamp(philo->table_p->start_time);
	print(philo, "is eating");
	usleep(philo->table_p->time_to_eat * 1000);
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
	print(philo, "is sleeping");
	usleep(philo->table_p->time_to_sleep * 1000);
	return (0);
}

int	_think(t_philo *philo)
{
	print(philo, "is thinking");
	usleep(100);
	return (0);
}

void	*routine(void *philo_struct)
{
	t_philo	*philo;

	philo = (t_philo *)philo_struct;
	if (philo->table_p->number_of_philos == 1)
	{
		print(philo, "has taken a fork");
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

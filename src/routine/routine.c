/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:17:32 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/15 10:14:14 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"
#include "run.h"
#include <unistd.h>

int	check_alive(t_philo *philo)
{
		pthread_mutex_lock(&philo->table_p->dead_mutex);
		if (philo->table_p->dead)
		{
			pthread_mutex_unlock(&philo->table_p->dead_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->table_p->dead_mutex);
		return (0);
}


void    _print(t_philo *philo, char *str)
{
	long long timestamp;

	pthread_mutex_lock(&philo->table_p->dead_mutex);
	pthread_mutex_lock(&philo->table_p->print_mutex);
	if (!philo->table_p->dead)
	{
		timestamp = get_time_stamp(philo->table_p->start_time);
		printf("%lld %i %s\n", timestamp, philo->id, str);
	}
	pthread_mutex_unlock(&philo->table_p->print_mutex);
	pthread_mutex_unlock(&philo->table_p->dead_mutex);
}

void    take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->mutex);
		_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->mutex);
		_print(philo, "has taken a fork");
	}
}

int _eat(t_philo *philo)
{
	if ((get_time_stamp(philo->table_p->start_time) - philo->start_dying) >= philo->table_p->time_to_die)
	{
		pthread_mutex_lock(&philo->table_p->dead_mutex);
		pthread_mutex_lock(&philo->table_p->print_mutex);
		printf("%i %i %s\n", get_time_stamp(philo->table_p->start_time), philo->id, "died");
		philo->table_p->dead = 1;
		pthread_mutex_unlock(&philo->table_p->print_mutex);
		pthread_mutex_unlock(&philo->table_p->dead_mutex);
		return (1);
	} 
	take_forks(philo);
	pthread_mutex_lock(&philo->table_p->dead_mutex);
	philo->start_dying = get_time_stamp(philo->table_p->start_time);
	pthread_mutex_unlock(&philo->table_p->dead_mutex);
	_print(philo, "is eating");
	usleep(philo->table_p->time_to_eat * 1000);
	// smart_sleep(philo, philo->table_p->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	philo->meal_count++;
	if (philo->meal_count == philo->table_p->number_of_meals)
		return (1);
	return (0);
}

int _sleep(t_philo *philo)
{
	if ((get_time_stamp(philo->table_p->start_time) - philo->start_dying) >= philo->table_p->time_to_die)
	{
		pthread_mutex_lock(&philo->table_p->dead_mutex);
		pthread_mutex_lock(&philo->table_p->print_mutex);
		printf("%i %i %s\n", get_time_stamp(philo->table_p->start_time), philo->id, "died");
		philo->table_p->dead = 1;
		pthread_mutex_unlock(&philo->table_p->print_mutex);
		pthread_mutex_unlock(&philo->table_p->dead_mutex);
		return (1);
	} 
	_print(philo, "is sleeping");
	usleep(philo->table_p->time_to_sleep * 1000);
	// smart_sleep(philo, philo->table_p->time_to_sleep * 1000);
	return (0);
}

int _think(t_philo *philo)
{
	if ((get_time_stamp(philo->table_p->start_time) - philo->start_dying) >= philo->table_p->time_to_die)
	{
		pthread_mutex_lock(&philo->table_p->dead_mutex);
		pthread_mutex_lock(&philo->table_p->print_mutex);
		printf("%i %i %s\n", get_time_stamp(philo->table_p->start_time), philo->id, "died");
		philo->table_p->dead = 1;
		pthread_mutex_unlock(&philo->table_p->print_mutex);
		pthread_mutex_unlock(&philo->table_p->dead_mutex);
		return (1);
	}
	_print(philo, "is thinking");
	usleep(100);
	return (0);
}

void *routine(void *philo_struct)
{
	t_philo *philo;

	philo = (t_philo *)philo_struct;
	if (philo->id % 2 != 0)
		usleep(100);
	while (1)
	{
		if (!check_alive(philo))
		{
			if (_eat(philo))
				break ;
		}
		if (!check_alive(philo))
		{
			if (_sleep(philo))
				break ;
		}
		if (!check_alive(philo))
		{
			if (_think(philo))
				break ;
		}
		if (check_alive(philo))
			break ;
	}
	return (NULL);
}

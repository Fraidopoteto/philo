/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:23:16 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/15 10:20:26 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"

void    start_timer(t_table *table)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	(*table).start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int	get_time_stamp(int start_time)
{
	long long int	time_stamp;
	struct  		timeval tv;

	gettimeofday(&tv, NULL);
	time_stamp = (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - start_time);
	return (time_stamp);
}

void smart_sleep(t_philo *philo, long long time_to_sleep)
{
	long long	start_time;

	start_time = get_time_stamp(philo->table_p->start_time);
	while ((get_time_stamp(philo->table_p->start_time) - start_time) < time_to_sleep)
	{
		if (check_alive(philo))
			break;
		usleep(1000);
	}
}
void	start_routine(t_table *table, t_philo **philo)
{
	int	i;

	i = 0;
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
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:31:06 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/16 21:03:42 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void    print(t_philo *philo, char *str)
{
	long long int	timestamp;

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

void	start_timer(t_table *table)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	(*table).start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

long long int	get_time_stamp(long long int start_time)
{
	long long int	time_stamp;
	struct  		timeval tv;

	gettimeofday(&tv, NULL);
	time_stamp = (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - start_time);
	return (time_stamp);
}
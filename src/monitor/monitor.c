/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:46:44 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/16 20:51:00 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"

static int	_all_have_eaten(t_philo **philo)
{
    int i;
    int	j;

    i = 0;
    j = 0;
    while (i < (*philo)->table_p->number_of_philos)
    {
        if ((*philo)[i].meal_count == (*philo)->table_p->number_of_meals)
            j++;
        i++;
    }
    if (j == (*philo)->table_p->number_of_philos)
        return (1);
    return (0);
}

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

void *monitor(void *philo_struct)
{
	t_philo 		*philo;
	int				i;
	long long int	last_meal_time;

	philo = (t_philo *)philo_struct;
	while (1)
	{
		if (_all_have_eaten(&philo))
			return (NULL);
		i = 0;
		while (i < philo->table_p->number_of_philos)
		{
			pthread_mutex_lock(&philo[i].data_mutex);
			last_meal_time = philo[i].start_dying;
			pthread_mutex_unlock(&philo[i].data_mutex);
			if ((get_time_stamp(philo[i].table_p->start_time) - last_meal_time) >= philo->table_p->time_to_die || philo[i].table_p->dead == 1)
			{
				pthread_mutex_lock(&philo->table_p->dead_mutex);
				pthread_mutex_lock(&philo->table_p->print_mutex);
				printf("%lli %i %s\n", get_time_stamp(philo[i].table_p->start_time), philo[i].id, "died");
				philo->table_p->dead = 1;
				pthread_mutex_unlock(&philo->table_p->print_mutex);
				pthread_mutex_unlock(&philo->table_p->dead_mutex);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

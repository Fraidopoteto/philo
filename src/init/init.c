/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:40:28 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/15 10:12:19 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

int    init(char **argv, t_table *table, t_philo **philo, t_fork **fork)
{
	int i;

	i = 0;
	table->dead = 0;
	table->number_of_philos = atoi(argv[1]);
	table->time_to_die = atoi(argv[2]);
	table->time_to_eat = atoi(argv[3]);
	table->time_to_sleep = atoi(argv[4]);
	table->number_of_meals = -1;
	*philo = calloc(table->number_of_philos, sizeof(t_philo));
	if (*philo == NULL)
		return (1);
	*fork = calloc(table->number_of_philos, sizeof(t_fork));
	if (*fork == NULL)
		return (1);
	pthread_mutex_init(&(*fork)->mutex, NULL);
	while(i < table->number_of_philos)
	{
		(*philo)[i].id = i;
		(*fork)[i].id = i;
		(*philo)[i].table_p = table;
		(*philo)[i].left_fork = &(*fork)[i];
		(*philo)[i].right_fork = &(*fork)[(i + 1) % table->number_of_philos];
		(*philo)[i].meal_count = 0;
		i++;
	}
	pthread_mutex_init(&(table->dead_mutex), NULL);
	pthread_mutex_init(&(table->print_mutex), NULL);
	return (0);
}

int    init_with_meals(char **argv, t_table *table, t_philo **philo, t_fork **fork)
{
	int i;

	i = 0;
	table->dead = 0;
	table->number_of_philos = atoi(argv[1]);
	table->time_to_die = atoi(argv[2]);
	table->time_to_eat = atoi(argv[3]);
	table->time_to_sleep = atoi(argv[4]);
	table->number_of_meals = atoi(argv[5]);
	*philo = calloc(table->number_of_philos + 1, sizeof(t_philo));
	if (*philo == NULL)
		return (1);
	*fork = calloc(table->number_of_philos + 1, sizeof(t_fork));
	if (*fork == NULL)
		return (1);
	while(i < table->number_of_philos)
	{
		(*philo)[i].id = i;
		(*fork)[i].id = i;
		(*philo)[i].table_p = table;
		(*philo)[i].left_fork = &(*fork)[i];
		(*philo)[i].right_fork = &(*fork)[(i + 1) % table->number_of_philos];
		(*philo)[i].meal_count = 0;
		pthread_mutex_init(&(*fork)[i].mutex, NULL);
		i++;
	}
	pthread_mutex_init(&(table->dead_mutex), NULL);
	pthread_mutex_init(&(table->print_mutex), NULL);
	return (0);
}

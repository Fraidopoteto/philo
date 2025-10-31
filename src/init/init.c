/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:40:28 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/31 18:00:09 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

int	ft_atol(const char *str)
{
	long long int	res;
	int				i;

	res = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > (LONG_MAX - (str[i] - '0')) / 10)
			return (-1);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return ((int)res);
}

int	init_args(char **argv, t_table *table)
{
	table->dead = 0;
	table->number_of_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->number_of_meals = -1;
	if (table->number_of_philos <= 0 || table->time_to_die <= 0 ||
		 table->time_to_eat <= 0 || table->time_to_sleep <= 0)
		return (1);
	return (0);
}

int	init(t_table *table, t_philo **philo, t_fork **fork)
{
	int	i;

	i = 0;
	*philo = calloc(table->number_of_philos, sizeof(t_philo));
	if (*philo == NULL)
		return (1);
	*fork = calloc(table->number_of_philos, sizeof(t_fork));
	if (*fork == NULL)
		return (1);
	while (i < table->number_of_philos)
	{
		(*philo)[i].id = i;
		(*fork)[i].id = i;
		(*philo)[i].table_p = table;
		(*philo)[i].left_fork = &(*fork)[i];
		(*philo)[i].right_fork = &(*fork)[(i + 1) % table->number_of_philos];
		(*philo)[i].meal_count = 0;
		pthread_mutex_init(&(*fork)[i].mutex, NULL);
		pthread_mutex_init(&(*philo)[i].data_mutex, NULL);
		i++;
	}
	pthread_mutex_init(&(table->dead_mutex), NULL);
	pthread_mutex_init(&(table->print_mutex), NULL);
	return (0);
}

int	init_args_with_meals(char **argv, t_table *table)
{
	table->dead = 0;
	table->number_of_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->number_of_meals = ft_atol(argv[5]);
	if (table->number_of_philos <= 0 || table->time_to_die <= 0 ||
		 table->time_to_eat <= 0 || table->time_to_sleep <= 0 ||
		 table->number_of_meals <= 0)
		return (1);
	return (0);
}

int	init_with_meals(t_table *table, t_philo **philo, t_fork **fork)
{
	int	i;

	i = 0;
	*philo = calloc(table->number_of_philos + 1, sizeof(t_philo));
	if (*philo == NULL)
		return (1);
	*fork = calloc(table->number_of_philos + 1, sizeof(t_fork));
	if (*fork == NULL)
		return (1);
	while (i < table->number_of_philos)
	{
		(*philo)[i].id = i;
		(*fork)[i].id = i;
		(*philo)[i].table_p = table;
		(*philo)[i].left_fork = &(*fork)[i];
		(*philo)[i].right_fork = &(*fork)[(i + 1) % table->number_of_philos];
		(*philo)[i].meal_count = 0;
		pthread_mutex_init(&(*fork)[i].mutex, NULL);
		pthread_mutex_init(&(*philo)[i].data_mutex, NULL);
		i++;
	}
	pthread_mutex_init(&(table->dead_mutex), NULL);
	pthread_mutex_init(&(table->print_mutex), NULL);
	return (0);
}

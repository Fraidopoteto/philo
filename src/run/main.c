/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:58 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/30 20:19:30 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "error.h"
#include "run.h"

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philo;
	t_fork	*fork;

	philo = NULL;
	fork = NULL;
	if (argc < 5)
		return (error("error: not enough arguments\n"));
	else if (argc == 5)
	{
		init_args(argv, &table);
		if (init(&table, &philo, &fork))
		return (1);
	}
	else if (argc == 6)
	{
		init_args_with_meals(argv, &table);
			if (init_with_meals(&table, &philo, &fork))
			return (1);
	}
	else if (argc > 6)
		return (error("error: too many arguments\n"));
	start_timer(&table, &philo);
	start_routine(&table, &philo);
	_free(philo, fork);
}

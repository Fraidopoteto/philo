/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:24:10 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/16 21:01:02 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

#include <stdlib.h>
#include <pthread.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_fork
{
	int	            id;
	t_mutex			mutex;
}	t_fork;

typedef struct s_table
{
    int             number_of_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             number_of_meals;
    long long int   start_time;
    int             dead;
    pthread_t       dead_thread;
    t_mutex			dead_mutex;
    t_mutex         print_mutex;
} t_table;

typedef struct s_philo
{
    int             id;
    t_fork          *left_fork;
    t_fork          *right_fork;
    pthread_t       thread;
    t_table         *table_p;
    long long int   start_dying;
    int             meal_count;
    t_mutex         data_mutex;
}   t_philo;


void	init_args(char **argv, t_table *table);
int	    init(t_table *table, t_philo **philo, t_fork **fork);
void	init_args_with_meals(char **argv, t_table *table);
int	    init_with_meals(t_table *table, t_philo **philo, t_fork **fork);


#endif
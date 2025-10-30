/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:26:04 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/28 14:36:12 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINE_H
# define ROUTINE_H

# include <unistd.h>
# include "init.h"
# include "monitor.h"
# include "utils.h"

void	*routine(void *philo);
int		check_alive(t_philo *philo);
void	*monitor(void *philo_struct);
int		_think(t_philo *philo);
int		_sleep(t_philo *philo);
int		_eat(t_philo *philo);
int		_take_forks(t_philo *philo);

#endif

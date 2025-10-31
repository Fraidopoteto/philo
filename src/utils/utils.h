/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:31:15 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/31 17:34:54 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include "init.h"
# include "routine.h"

void			print(t_philo *philo, char *str);
void			start_timer(t_table *table, t_philo **philo);
long long int	get_time_stamp(long long int start_time);
int				routine_split(t_philo **philo);
void			_free(t_philo *philo, t_fork *fork);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:27:24 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/07 20:38:26 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

#include <pthread.h>
#include <sys/time.h>
#include "init.h"
#include "routine.h"


void    start_timer(t_table *table);
void	start_routine(t_table *table, t_philo **philo);
int     get_time_stamp(int start_time);


#endif
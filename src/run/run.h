/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:27:24 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/30 21:15:17 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# include <pthread.h>
# include "init.h"
# include "routine.h"

void			start_routine(t_table *table, t_philo **philo);
long long int	get_time_stamp(long long int start_time);
int				smart_sleep(t_philo *philo, int time);

#endif

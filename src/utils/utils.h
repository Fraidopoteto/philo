/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:31:15 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/16 21:04:07 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include "init.h"


void			print(t_philo *philo, char *str);
void			start_timer(t_table *table);
long long int	get_time_stamp(long long int start_time);


#endif
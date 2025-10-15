/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:26:04 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/15 10:05:26 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ROUTINE_H
# define ROUTINE_H

#include <stdio.h>
#include <unistd.h>
#include "init.h"

void    *routine(void *philo);
int     check_alive(t_philo *philo);


#endif
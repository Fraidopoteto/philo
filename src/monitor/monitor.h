/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joschmun <joschmun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:46:39 by joschmun          #+#    #+#             */
/*   Updated: 2025/10/28 12:11:19 by joschmun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include "init.h"
# include "utils.h"

int		check_alive(t_philo *philo);
void	*monitor(void *philo_struct);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:27:43 by hoel-har          #+#    #+#             */
/*   Updated: 2026/03/17 15:49:14 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <threads.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <stdbool.h>

typedef struct s_params
{
	long		nb_philo;
	long		time_die;
	long		time_eat;
	long		time_sleep;
	long		*ids;
	long		*nb_fork;
	long		must_eat;
	long		limit_meal;
	bool		all_threads_ready;
	pthread_t	*threads;
	t_params	*philo;
}	t_params;

typedef struct s_philo
{
	int			meal_count;
	long		lst_meal;
	t_params	*params;
}	t_philo;


int	check_and_init(int ac, char **av, t_philo *philo);

#include "parsing.h"

#endif 

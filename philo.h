/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:27:43 by hoel-har          #+#    #+#             */
/*   Updated: 2026/03/16 18:08:26 by hoel-har         ###   ########.fr       */
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

typedef struct s_params
{
	int			nb_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			must_eat;
	pthread_t	*threads;
	int			*nb_fork;
	
}	t_params;

typedef struct s_philo
{
	int			nb_philo;
	int			meal_count;
	long		lst_meal;
	t_params	*params;
}	t_philo;


int	check_and_init(int ac, char **av, t_philo *philo);

#include "parsing.h"

#endif 

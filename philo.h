/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:27:43 by hoel-har          #+#    #+#             */
/*   Updated: 2026/03/18 11:46:50 by hoel-har         ###   ########.fr       */
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

typedef	struct s_params t_params;


typedef struct s_fork
{
	int				id_fork;
	pthread_mutex_t fork;
}	t_fork;

typedef struct s_philo
{
	int			id;
	long		meal_count;
	long		time_lst_meal;
	bool		full;
	pthread_t	*threads;
	t_fork		*rigth_fork;
	t_fork		*left_fork;
	t_params	*params;
}	t_philo;

typedef struct s_params
{
	long			nb_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			*ids;
	long			*nb_fork;
	long			must_eat;
	long			beg_dinner;
	long		 	limit_meal;
	bool			all_threads_ready;
	t_fork			*forks;
	pthread_mutex_t *mutex_waiting_thread;
	t_philo			*philo;
}	t_params;


typedef enum	e_mutsec
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACHE,	
}	t_mutsec;

int	check_and_init(int ac, char **av, t_philo *philo);

#include "parsing.h"

#endif 

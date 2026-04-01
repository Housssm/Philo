/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:27:43 by hoel-har          #+#    #+#             */
/*   Updated: 2026/04/01 12:36:01 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <threads.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <string.h>

typedef	struct s_data t_data;

typedef struct s_fork
{
	int				id_fork;
	pthread_mutex_t fork;
}	t_fork;


typedef	struct s_philo
{
	int				id;
	long			meal_count;
	long			time_lst_meal;
	bool			full;
	bool			thread_ready;
	long			time;
	pthread_t		threads_ids;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_data			*data;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
	
} t_philo;

typedef struct s_data
{
	long			nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat;
	long			start_time;
	bool			dead;
	bool			time_starded;
	t_fork			*forks; // Vraiment utile ?
	pthread_t	assas;
	pthread_mutex_t	time_lock;
	pthread_mutex_t	table_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philo;

}	t_data;

typedef enum	e_mutsec
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACHE,
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
}	t_mutsec;

int		check_and_init(int ac, char **av, t_data *data);
void	free_struct(t_data *data);
void	determine_fork(t_philo *philo, t_fork *forks, int position);



#include "parsing.h"

#endif 

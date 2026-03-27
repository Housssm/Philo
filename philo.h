/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:27:43 by hoel-har          #+#    #+#             */
/*   Updated: 2026/03/27 12:58:08 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <threads.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

typedef	struct s_data t_data;


typedef struct s_fork
{
	int				id_fork;
	pthread_mutex_t fork;
}	t_fork;

// typedef struct s_philo
// {
// 	int			id;//
// 	long		meal_count;//
// 	long		time_lst_meal;//
// 	bool		full;//
// 	pthread_t	*threads_id;//
// 	t_fork		*first_fork;
// 	t_fork		*second_fork;
// 	t_params	*params;
// }	t_philo;

// typedef struct s_params
// {
// 	long			nb_philo;//
// 	long			time_die;//
// 	long			time_eat;//
// 	long			time_sleep;//
// 	long			*nb_fork;
// 	long			must_eat;//
// 	long			beg_dinner;
// 	long		 	limit_meal;
// 	bool			all_threads_ready;//
// 	t_fork			*forks;//
// 	pthread_mutex_t *mutex_waiting_thread;
// 	t_philo			*philos;
// }	t_params;

typedef	struct s_philo
{
	int				id;
	long			meal_count;
	long			time_lst_meal;
	bool			full;
	__uint64_t		start_time;
	__uint64_t		end_time;
	size_t			time;
	pthread_t		threads_ids;
	bool			thread_ready;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_data			*data;
	
} t_philo;

typedef struct s_data
{
	long			nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat;
	t_fork			*forks;
	pthread_mutex_t	table_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
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
}	t_mutsec;

int		check_and_init(int ac, char **av, t_data *data);
void	free_struct(t_data *data);


#include "parsing.h"

#endif 

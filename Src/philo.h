/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:27:43 by hoel-har          #+#    #+#             */
/*   Updated: 2026/04/12 16:54:29 by hoel-har         ###   ########.fr       */
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

typedef struct s_data	t_data;

typedef struct s_fork
{
	int				id_fork;
	pthread_mutex_t	fork;
}	t_fork;

typedef struct s_philo
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
}	t_philo;

typedef struct s_data
{
	long			nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat;
	long			start_time;
	long			nb_philo_full;
	bool			dead;
	bool			full;
	bool			time_starded;
	t_fork			*forks;
	pthread_t		assas;
	pthread_mutex_t	time_lock;
	pthread_mutex_t	count_lock;
	pthread_mutex_t	table_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philo;

}	t_data;

typedef enum e_mutsec
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
int		safe_mutex(pthread_mutex_t *mutex, t_mutsec opcode);
void	fill_first_part(char **av, t_data *data);
int		all_mutexes_initialisation(t_data *data);
long	ft_atol(const char *s);
void	free_struct(t_data *data);
void	release_forks(t_philo *philo);
bool	take_second_fork_interruptible(t_philo *philo);
void	wait_start(t_data *data);
void	safe_writting(t_philo *philo, t_mutsec opcode);
int		safe_thread(
			pthread_t *thread,
			void*(*fct)(void *),
			void *data,
			t_mutsec opcode);
void	eating(t_philo *philo);
void	which_action(t_philo *philo, t_mutsec opcode);
void	*what_to_do(void *data);
int		a_table(t_data *data);
int		lonely(t_data *data);
bool	all_philos_full(t_data *data);
void	mark_full_and_stop(t_data *data);
bool	check_one_death(t_data *data, int i);
void	*check_dead(void *dato);
bool	is_dead(t_data *data);
bool	is_full(t_data *data);
void	set_dead(t_data *data, bool value);
long	get_time(void);
void	precise_sleep(t_data *data, long ms);

#endif 

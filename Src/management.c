/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:33:44 by hoel-har          #+#    #+#             */
/*   Updated: 2026/04/12 16:39:30 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_thread(pthread_t *thread, void*(*fct)(void *)
, void *data, t_mutsec opcode)
{
	if (opcode == CREATE)
		return (pthread_create(thread, NULL, fct, data));
	else if (opcode == DETACHE)
		return (pthread_detach(*thread));
	else if (opcode == JOIN)
		return (pthread_join(*thread, NULL));
	else
		return (printf("Invalide opcode for thread\n"), 1);
}

void	safe_writting(t_philo *philo, t_mutsec opcode)
{
	long	time;

	safe_mutex(&philo->data->time_lock, LOCK);
	if (philo->data->dead && opcode != DIE)
		return (safe_mutex(&philo->data->time_lock, UNLOCK), (void)0);
	time = get_time() - philo->data->start_time;
	safe_mutex(&philo->data->write_lock, LOCK);
	philo->time = get_time() - philo->data->start_time;
	if (opcode == FORK)
		printf("%ld %d has taken a fork\n", time, philo->id);
	else if (opcode == EAT)
		printf("%ld %d is eating\n", time, philo->id);
	else if (opcode == SLEEP)
		printf("%ld %d is sleeping\n", time, philo->id);
	else if (opcode == THINK)
		printf("%ld %d is thinking\n", time, philo->id);
	else if (opcode == DIE)
		printf("%ld %d died\n", time, philo->id);
	safe_mutex(&philo->data->write_lock, UNLOCK);
	safe_mutex(&philo->data->time_lock, UNLOCK);
}

void	wait_start(t_data *data)
{
	while (1)
	{
		safe_mutex(&data->table_lock, LOCK);
		if (data->time_starded)
		{
			safe_mutex(&data->table_lock, UNLOCK);
			return ;
		}
		safe_mutex(&data->table_lock, UNLOCK);
		usleep(10);
	}
}

bool	take_second_fork_interruptible(t_philo *philo)
{
	while (!is_dead(philo->data) && !is_full(philo->data))
	{
		if (pthread_mutex_trylock(&philo->second_fork->fork) == 0)
			return (true);
		usleep(200);
	}
	return (false);
}

void	release_forks(t_philo *philo)
{
	safe_mutex(&philo->second_fork->fork, UNLOCK);
	safe_mutex(&philo->first_fork->fork, UNLOCK);
}

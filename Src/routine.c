/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 16:14:12 by hoel-har          #+#    #+#             */
/*   Updated: 2026/04/12 17:58:17 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	safe_mutex(&philo->first_fork->fork, LOCK);
	safe_writting(philo, FORK);
	if (is_dead(philo->data) || is_full(philo->data))
	{
		safe_mutex(&philo->first_fork->fork, UNLOCK);
		return ;
	}
	if (!take_second_fork_interruptible(philo))
	{
		safe_mutex(&philo->first_fork->fork, UNLOCK);
		return ;
	}
	safe_writting(philo, FORK);
	if (is_dead(philo->data) || is_full(philo->data))
	{
		release_forks(philo);
		return ;
	}
	safe_mutex(&philo->meal_lock, LOCK);
	philo->meal_count += 1;
	philo->time_lst_meal = get_time();
	safe_mutex(&philo->meal_lock, UNLOCK);
	safe_writting(philo, EAT);
	precise_sleep(philo->data, philo->data->time_to_eat);
	release_forks(philo);
}

void	which_action(t_philo *philo, t_mutsec opcode)
{
	long	think_time;

	if (opcode == SLEEP)
	{
		safe_writting(philo, SLEEP);
		precise_sleep(philo->data, philo->data->time_to_sleep);
	}
	if (opcode == THINK)
	{
		safe_writting(philo, THINK);
		think_time = 0;
		if (philo->data->nb_philos % 2 != 0)
		{
			think_time = (philo->data->time_to_eat * 2)
				- philo->data->time_to_sleep;
			if (think_time < 1)
				think_time = 1;
		}
		if (think_time > 0)
			precise_sleep(philo->data, think_time);
	}
}

void	*what_to_do(void *data)
{
	t_philo	*philo;

	philo = data;
	wait_start(philo->data);
	if (philo->id % 2 == 0)
		precise_sleep(philo->data, philo->data->time_to_eat / 2);
	while (!is_dead(philo->data))
	{
		eating(philo);
		if (is_dead(philo->data) || is_full(philo->data))
			break ;
		which_action(philo, SLEEP);
		which_action(philo, THINK);
	}
	return (NULL);
}

int	lonely(t_data *data)
{
	data->start_time = get_time();
	data->philo[0].time_lst_meal = data->start_time;
	safe_writting(&data->philo[0], FORK);
	precise_sleep(data, data->time_to_die);
	set_dead(data, true);
	safe_writting(&data->philo[0], DIE);
	return (0);
}

int	a_table(t_data *data)
{
	int	i;

	if (data->nb_philos == 1)
		return (lonely(data));
	i = -1;
	while (++i < data->nb_philos)
		if (safe_thread(&data->philo[i].threads_ids,
				what_to_do, &data->philo[i], CREATE))
			return (1);
	if (safe_thread(&data->assas, check_dead, data, CREATE))
		return (3);
	safe_mutex(&data->table_lock, LOCK);
	data->start_time = get_time();
	i = -1;
	while (++i < data->nb_philos)
		data->philo[i].time_lst_meal = data->start_time;
	data->time_starded = true;
	safe_mutex(&data->table_lock, UNLOCK);
	i = -1;
	while (++i < data->nb_philos)
		if (safe_thread(&data->philo[i].threads_ids, NULL, NULL, JOIN))
			return (1);
	if (safe_thread(&data->assas, NULL, NULL, JOIN))
		return (4);
	return (0);
}

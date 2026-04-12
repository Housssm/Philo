/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 16:20:40 by hoel-har          #+#    #+#             */
/*   Updated: 2026/04/12 16:43:19 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	all_philos_full(t_data *data)
{
	int		i;
	int		full_count;
	long	meal_count;

	if (data->must_eat == -1)
		return (false);
	full_count = 0;
	i = -1;
	while (++i < data->nb_philos)
	{
		safe_mutex(&data->philo[i].meal_lock, LOCK);
		meal_count = data->philo[i].meal_count;
		safe_mutex(&data->philo[i].meal_lock, UNLOCK);
		if (meal_count >= data->must_eat)
			full_count++;
	}
	return (full_count == data->nb_philos);
}

void	mark_full_and_stop(t_data *data)
{
	safe_mutex(&data->count_lock, LOCK);
	data->full = true;
	safe_mutex(&data->count_lock, UNLOCK);
	set_dead(data, true);
}

bool	check_one_death(t_data *data, int i)
{
	long	last_meal;

	safe_mutex(&data->philo[i].meal_lock, LOCK);
	last_meal = data->philo[i].time_lst_meal;
	safe_mutex(&data->philo[i].meal_lock, UNLOCK);
	if ((get_time() - last_meal) <= data->time_to_die)
		return (false);
	safe_mutex(&data->time_lock, LOCK);
	if (!data->dead)
	{
		data->dead = true;
		safe_mutex(&data->write_lock, LOCK);
		printf("%ld %d died\n", get_time() - data->start_time,
			data->philo[i].id);
		safe_mutex(&data->write_lock, UNLOCK);
	}
	safe_mutex(&data->time_lock, UNLOCK);
	return (true);
}

void	*check_dead(void *dato)
{
	t_data	*data;
	int		i;

	data = (t_data *)dato;
	wait_start(data);
	while (!is_dead(data))
	{
		if (all_philos_full(data))
			return (mark_full_and_stop(data), NULL);
		i = -1;
		while (++i < data->nb_philos && !is_dead(data))
			if (check_one_death(data, i))
				return (NULL);
		usleep(1000);
	}
	return (NULL);
}

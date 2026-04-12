/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 16:24:47 by hoel-har          #+#    #+#             */
/*   Updated: 2026/04/12 16:50:30 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(t_data *data)
{
	bool	result;

	safe_mutex(&data->time_lock, LOCK);
	result = data->dead;
	safe_mutex(&data->time_lock, UNLOCK);
	return (result);
}

bool	is_full(t_data *data)
{
	bool	result;

	safe_mutex(&data->count_lock, LOCK);
	result = data->full;
	safe_mutex(&data->count_lock, UNLOCK);
	return (result);
}

void	set_dead(t_data *data, bool value)
{
	safe_mutex(&data->time_lock, LOCK);
	data->dead = value;
	safe_mutex(&data->time_lock, UNLOCK);
}

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * (long)1000) + (time.tv_usec / 1000));
}

void	precise_sleep(t_data *data, long ms)
{
	long	start;
	long	now;

	start = get_time();
	while (!is_dead(data))
	{
		now = get_time();
		if (now - start >= ms)
			break ;
		usleep(1000);
	}
}

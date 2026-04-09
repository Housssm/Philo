/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:36:52 by hoel-har          #+#    #+#             */
/*   Updated: 2026/04/09 19:22:58 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *s)
{
	int			i;
	long int	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((s[i] > 8 && s[i] < 14) || s[i] == ' ')
			i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
				sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
			res = res * 10 + s[i] - 48;
			i++;
	}
	return (res * sign);
}

void	fill_first_part(char **av, t_data *data)
{
	data->nb_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->must_eat = ft_atol(av[5]);
	else
		data->must_eat = -1;
	data->dead = false;
	data->full = false;
	data->time_starded = false;
	data->start_time = 0;
	data->nb_philo_full = 0;
}

int	all_mutexes_initialisation(t_data *data)
{
	if (safe_mutex(&data->table_lock, INIT))
		return (printf("Error initialisation mutexe table\n"), 1);
	if (safe_mutex(&data->write_lock, INIT))
		return (printf("Error initialisation mutexe writting\n"), 2);
	if (safe_mutex(&data->time_lock, INIT))
		return (printf("Error initialisation mutexe time\n"), 3);
	if (safe_mutex(&data->count_lock, INIT))
		return (printf("Error initialisation mutexe time\n"), 5);
	return (0);
}

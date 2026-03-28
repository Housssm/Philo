/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:29:54 by hoel-har          #+#    #+#             */
/*   Updated: 2026/03/28 16:47:10 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "philo.h"

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

int	safe_mutex(pthread_mutex_t *mutex, t_mutsec opcode)
{
	if (opcode == LOCK)
		return (pthread_mutex_lock(mutex));
	else if (opcode == UNLOCK)
		return (pthread_mutex_unlock(mutex));
	else if (opcode == INIT)
		return (pthread_mutex_init(mutex, NULL));
	else if (opcode == DESTROY)
		return (pthread_mutex_destroy(mutex));
	else
		return (printf("Wrong opcode for mutex\n"), 1);
	return (0);
}

void	determine_fork(t_philo *philo, t_fork *forks, int position)
{
	int	nb_philo;

	nb_philo = philo->data->nb_philos;
	philo->first_fork = &forks[(position + 1) % nb_philo];
	philo->second_fork = &forks[position];
	if (philo->id % 2)
	{
		philo->first_fork = &forks[position];
		philo->second_fork = &forks[(position + 1) % nb_philo];
	}
}

void	fill_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < data->nb_philos)
	{
		philo = data->philo + i;
		philo->id = i + 1;
		philo->meal_count = 0;
		philo->time_lst_meal = 0;
		philo->full = false;
		philo->data = data;
		philo->threads_ids = i + 1;
		// philo->end_time = 0;
		// philo->time = &philo->end_time - &philo->start_time; // demander confirmatiom
		philo->thread_ready = false;
		determine_fork(philo, data->forks, i);
		if (safe_mutex(&philo->meal_lock, INIT))
			return (printf("Erreur minitialisation mutexe meal\n"), 1);
		if (safe_mutex(&philo->dead_lock, INIT))
			return (printf("Erreur minitialisation mutexe dead\n"), 1)
	}
}

int	all_mutexes_initialisation(t_data *data)
{
	if (safe_mutex(&data->table_lock, INIT))
		return (("Error initialisation mutexe table\n"), 1);
	if (safe_mutex(&data->write_lock, INIT))
		return (("Error initialisation mutexe writting\n"), 2);
	if (safe_mutex(&data->time_lock, INIT))
		return (("Error initialisation mutexe time\n"), 3);
	// if (safe_mutex(&data->table_lock, INIT))
	// 	return (3);
	return (0);
}

int	fill_data(char **av, t_data *data)
{
	int	i;

	i = -1;
	data->nb_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->must_eat = ft_atol(av[5]);
	data->philo = malloc(sizeof(t_philo) * data->nb_philos);
	data->forks = malloc(sizeof(t_fork) * data->nb_philos);
	data->dead = false;
	data->time_starded = false;
	data->start_time = 0;
	if (!data->philo || !data->forks)
		return (printf("Malloc probleme\n"), 1);
	while (++i < data->nb_philos)
	{
		if (safe_mutex(&data->forks[i].fork, INIT))
			return (2);
		data->forks[i].id_fork = i;
	}
	if (all_mutexes_initialisation(data))
		return (printf(3));
	fill_philo(data);

	return (0);
}

int	check_and_init(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	data->philo = NULL;
	data->forks = NULL;
	while (i < ac)
	{
		if (ft_atol(av[i]) < 0 || ft_atol(av[i]) > INT_MAX)
			return (printf("Invalid argument\n"), 1);
		i++;
	}
	if (av[5] && ft_atol(av[5]) == 0)
		return (printf("No simulation needed\n"), 1);
	if (fill_data(av, data))
		return (2);
	return (0);
}

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:29:54 by hoel-har          #+#    #+#             */
/*   Updated: 2026/03/18 18:15:39 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

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

void	determine_fork(t_philo *philo, t_fork *fork, int position)
{
	int	num_philo;

	num_philo = philo->params->nb_philo;
	
	philo->first_fork = &fork[(position + 1) % num_philo];
	philo->second_fork = &fork[position];
	if (philo->id % 2)
	{
		philo->first_fork = &fork[position];
		philo->second_fork = &fork[(position + 1) % num_philo];		
	}
}

int	fill_philo(t_params *params)
{
	int		i;
	t_philo *philo;

	i = -1;
	params->philos->threads_id = malloc(sizeof(pthread_t) * (params->nb_philo));
	if (!params->philos->threads_id)
		return (printf("Thread malloc problem\n"), 1);
	while (++i< params->nb_philo)
	{
		philo = params->philos + i;
		philo->id = i + 1;
		// printf(" value of philo id = %d\n\n\n\n", philo->id);
		philo->meal_count = 0;
		philo->full = false;
		philo->params = params;
		philo->threads_id = params->philos->threads_id;
		determine_fork(philo, params->forks, i);
	}
	return (0);
}

int	safe_mutex_handle(pthread_mutex_t *mutex, t_mutsec opcode)
{
	if (LOCK == opcode)
		return(pthread_mutex_lock(mutex));
	else if (UNLOCK == opcode)
		return(pthread_mutex_unlock(mutex));
	else if (DESTROY == opcode)
		return (pthread_mutex_destroy(mutex));
	else if (INIT == opcode)
		return (pthread_mutex_init(mutex, NULL));
	else 
		return (printf("Wrong opcode for mutex\n"), 1);
	return (0);
}

int	fill_params(char **av, t_params *params)
{
	int	i;

	i = -1;
 	// if ((ft_atol(av[1]) > INT_MAX)|| ft_atol(av[2]) > INT_MAX || ft_atol(av[3]) > INT_MAX || ft_atol(av[4]) > INT_MAX || (ft_atol(av[5]) && ft_atol(av[5]) > INT_MAX))
	// 	return (printf("Parameter's scope invalid\n"), 1);
	params->nb_philo = ft_atol(av[1]);
	params->time_die = ft_atol(av[2]) * 1e3;
	params->time_eat = ft_atol(av[3]) * 1e3;
	params->time_sleep = ft_atol(av[4]) * 1e3;
	if (av[5])
		params->must_eat = ft_atol(av[5]);
	else
		params->must_eat = -1;
	params->all_threads_ready = false;
	params->forks = malloc(sizeof(t_fork) * (params->nb_philo));
	if (!params->forks)
		return (printf("Error malloc forks\n"), 1);
	params->all_threads_ready = false;
	while (++i < ft_atol(av[1]))
	{
		if (safe_mutex_handle(&params->forks[i].fork, INIT))
			return (1);
	}
	params->philos = malloc(sizeof(t_philo) * params->nb_philo);
	if (!params->philos)
		return(printf("Error malloc philos\n"), 1);
	if (fill_philo(params))
		return (1);
	return(0);
}

int	check_and_init(int ac, char **av, t_philo *philo)
{
	int	i;

	i = 0;
	while ( i < ac)
	{
		if(ft_atol(av[i]) < 0)
			return (printf("Invalid argument\n"), 1);
		i++;
	}
	if (fill_params(av,philo->params))
		return (1);
	return (0);
}

#endif
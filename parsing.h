/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:29:54 by hoel-har          #+#    #+#             */
/*   Updated: 2026/03/16 18:16:06 by hoel-har         ###   ########.fr       */
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

int	fill_structs(char **av, t_params *params)
{

	params->nb_philo = ft_atol(av[1]);
	params->time_die = ft_atol(av[2]);
	params->time_eat = ft_atol(av[3]);
	params->time_sleep = ft_atol(av[4]);
	if (av[5])
	params->must_eat = ft_atol(av[5]);
	params->threads = malloc(sizeof(pthread_t *) * (params->nb_philo));
	if (!params->threads)
		return (1);
	params->nb_fork = malloc(sizeof(int *) * (params->nb_philo));
	if (!params->nb_fork)
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
	if (fill_structs(av,philo->params))
		return (1);
	return (0);
}

#endif
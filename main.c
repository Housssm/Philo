/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:26:41 by hoel-har          #+#    #+#             */
/*   Updated: 2026/03/09 14:40:12 by hoel-har         ###   ########.fr       */
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

void	fill_structs(char **av, t_philo *philo)
{
		philo->params->nb_philo = ft_atol(av[1]);
		philo->params->time_die = ft_atol(av[2]);
		philo->params->time_eat = ft_atol(av[3]);
		philo->params->time_sleep = ft_atol(av[4]);
//      philo->,must_eat = ft_atol(av[5]);
}

int	check_params(int ac, char **av, t_philo *philo)
{
	int	i;

	i = 0;
	while ( i < ac)
	{
		if(ft_atol(av[i]) < 0)
			return (printf("Invalid argument\n"), 1);
		i++;
	}
	fill_structs(av, philo);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo		philo;
	t_params	params;

	philo.params = &params;
	if (ac !=  6)
		return(printf("Invalid number of argument\n"), 1);
	if (check_params(ac, av, &philo))
		return (1);
	printf("%ld == %d\n",ft_atol(av[1]), philo.params->nb_philo);
	printf("%ld == %d\n",ft_atol(av[2]), philo.params->time_eat);
	printf("%ld == %d\n",ft_atol(av[3]), philo.params->time_die);
	printf("%ld == %d\n",ft_atol(av[4]), philo.params->time_sleep);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:26:41 by hoel-har          #+#    #+#             */
/*   Updated: 2026/03/16 18:15:02 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


//creer une structure pour la fourchette
//creer un droit dacces a la fourchette en regardant qui a le moins manger, si deux sont a egalite regarder qui na pas manger depuis le plus logntemps 
//creer un nb de mutex correspondant au nombre de fourchette ?
//faire des sleep correspondant au parametre, sleep pour temps de sommeil , tems de nouriture etc



// creer un nombre de threah egale au nombre de pilo 
//chque fourchette pour charque philo que oon doit proteger avec un mutex


void	free_struct(t_params *params)
{
	if (params->threads)
		free(params->threads);
	if (params->nb_fork)
		free(params->nb_fork);
}



void*	what_to_do(void *arg)
{
	(void)arg;
	printf("Passed by here\n");
	return NULL;
}

int	thread_launching(t_params *params)
{
	int	i;

	i = 0;
	while (i < params->nb_philo)
	{
		if (pthread_create(&params->threads[i], NULL, what_to_do, NULL) != 0)
			return (free_struct(params), 1);
		i++;
	}
	i = 0;
	while (i < params->nb_philo)
	{
		if (pthread_join(params->threads[i], NULL) != 0 )
			return (free_struct(params), 1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo		philo;
	t_params	params;
	
	philo.params = &params;
	if (ac == 5 || ac ==6 )
	{
		if (check_and_init(ac, av, &philo))
			return (1);
		if (thread_launching(&params))
			return (1);
		
		printf("nb philo    == %d\n", philo.params->nb_philo);
		printf("time to eat == %d\n", philo.params->time_eat);
		printf("time die    == %d\n", philo.params->time_die);
		printf("time sleep  == %d\n", philo.params->time_sleep);
	}
	else
		return(printf("Invalid number of argument\n"), 1);
	return (0);
}


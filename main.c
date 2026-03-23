/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:26:41 by hoel-har          #+#    #+#             */
/*   Updated: 2026/03/23 12:00:46 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//safe malloc 37.21


//creer une structure pour la fourchette
//creer un droit dacces a la fourchette en regardant qui a le moins manger, si deux sont a egalite regarder qui na pas manger depuis le plus logntemps 
//creer un nb de mutex correspondant au nombre de fourchette ?
//faire des sleep correspondant au parametre, sleep pour temps de sommeil , tems de nouriture etc



// creer un nombre de threah egale au nombre de pilo 
//chque fourchette pour charque philo que oon doit proteger avec un mutex
// proteger lecriture par un mutex aussi 

// void action(int nb_philo, char **message, int time)
// {
// 	if ( message == "fork")
// 	{	
// 		printf("%d %d has taken a fork\n", time, nb_philo);
// 		usleep(time);
// 	}
// 	if ( message == "eating")
// 	{	
// 		printf("%d %d is eating\n", time, nb_philo);
// 		usleep(time);
// 	}
// 	if ( message == "sleeping")
// 	{	
// 		printf("%d %d is sleeping\n", time, nb_philo);
// 		usleep(time);
// 	}
// 	if ( message == "thinking")
// 	{	
// 		printf("%d %d is thinking\n", time, nb_philo);
// 		usleep(time);
// 	}
// 	if ( message == "dead")
// 		printf("%d %d is dead\n", time, nb_philo);
// }
 
// void	free_struct(t_params *params)
// {	
// /* 	need to free philo->threads_id  params->forks params->philos intialise dans parsing
//  */	(void)params;
// 	int	i;
// 	i = -1;
	
// 	if (params->philos)
// 		printf("TEST\n");
// 	//destroy mutex
// }


// void*	what_to_do(void *structure)
// {
// 	t_philo *philo;
	
// 	philo = (t_philo *)structure;
// 	// wait_for_threads(philo->params);
// 	printf("passed here\n");
// 	sleep(3);
// 	return NULL;
// }

// int	a_table(t_params *params)
// {
// 	long	i;

// 	i = 0;
// 	if (params->must_eat == 0)
// 		return (0);
// 	while (i < params->nb_philo)
// 	{
// 		// params->ids[i] = i;
// 		if (pthread_create(&params->philos->threads_id[i], NULL, what_to_do, (void *)i )!= 0)
// 			return (free_struct(params), 1);
// 		printf("Thread %ld has started\n", i);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < params->nb_philo)
// 	{
// 		if (pthread_join(params->philos->threads_id[i], NULL) != 0 )
// 			return (free_struct(params), 1);
// 		printf("Thread %ld has finished\n", i);
// 		i++;
// 	}

// 	return (0);
// }
 
void	free_struct(t_data *data) // data philo et data forks
{
	int	i;

	i = 0;
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
}


int	main(int ac, char **av)
{
	t_philo		philo;
	t_data	data;
	
	philo.data = &data;
	data.philo = &philo;
	if (ac == 5 || ac ==6 )
	{
		if (check_and_init(ac, av, &data))
			return (free_struct(&data), 1);
		// if (a_table(&params))
		// 	return (free_struct(&params), 1);
	}
	else
		return(printf("Invalid number of argument\n"), 1);
	free_struct(&data);
	return (0);
}


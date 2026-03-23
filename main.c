/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:26:41 by hoel-har          #+#    #+#             */
/*   Updated: 2026/03/23 19:11:47 by hoel-har         ###   ########.fr       */
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
	if (data->philo != NULL)
		free(data->philo);
	if (data->forks != NULL)
		free(data->forks);
}

void	set_bool(data)

int	safe_thread(pthread_t *thread, void*(*fct)(void *),void *data, t_mutsec opcode)
{
	if (opcode == CREATE)
		return (pthread_create(thread, NULL, fct, data));
	else if (opcode == DETACHE)
		return (pthread_detach(*thread));
	else if (opcode == JOIN)
		return (pthread_join(*thread, NULL));
	else 
		return(printf("Invalide opcode for thread\n") ,1);
	return(0);
}

__uint64_t get_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		return(0);
	return ((tv.tv_sec * (__uint64_t)10000) + (tv.tv_sec / 1000));
}

void wait_for_threads(t_data *data)
{
	while (!get_bool(data->))
}


void*	what_to_do(void *data)
{
	t_philo *philo;
	
	philo = data;
	
	philo->start_time = get_time();
	usleep(10000);
	philo->end_time = get_time();
	printf("thread %d est passe par ici au temps %ld\n", philo->id, philo->end_time - philo->start_time);
	return NULL;
}
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	safe_mutex(mutex, LOCK);
	dest = value;
	safe_mutex(mutex, UNLOCK);
}

bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool result;
	
	safe_mutex(mutex, LOCK);
	result = *value;
	safe_mutex(mutex, UNLOCK);
	return (result);
}

int	a_table(t_data *data)
{
	int	i;
	
	i = -1;
	if ( data->nb_philos == 1)
		;//fonction a faire;
	else 
	{
		while(++i < data->nb_philos)
		{
			if (safe_thread(&data->philo[i].threads_ids, what_to_do, &data->philo[i], CREATE))
				return (1);
		}
		set_bool(&data->table_lock, &data->all_threads_ready, true);
		i = -1;
		while (++i < data->nb_philos)
		{
			if (safe_thread(&data->philo[i].threads_ids, what_to_do, NULL, JOIN))
				return (1);
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	philo;
	t_data	data;
	
	philo.data = &data;
	data.philo = &philo;
	if (ac == 5 || ac ==6 )
	{
		if (check_and_init(ac, av, &data))
			return (free_struct(&data), 1);
		if (a_table(&data))
			return (free_struct(&data), 1);
	}
	else
		return(printf("Invalid number of argument\n"), 1);
	free_struct(&data);
	return (0);
}


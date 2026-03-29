/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:26:41 by hoel-har          #+#    #+#             */
/*   Updated: 2026/03/29 18:21:04 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//les actions n sont pas coherentes
//faire en sorte que lordre daffichage soit en fonction du temops et non pas des threads
//verifier si laffichage se fait buien en milliseconde



void	free_struct(t_data *data) // data philo et data forks
{
	if (data->philo != NULL)
		free(data->philo);
	if (data->forks != NULL)
		free(data->forks);

	//safe_mutex(DESTROY); destroy all the mutexes
		
}

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


//TIME 

long get_time(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL))
		return(0);
	return ((time.tv_sec * (long)1000) + (time.tv_usec / 1000));
}
	
void set_bool(t_data *data, int i, bool value)
{
	data->philo[i].thread_ready = value;
}


bool	get_bool(bool *value)
{
	bool	result;

	result = value;
	return (result);
}

void	wait_for_threads(t_philo *philo)
{	
	while (!get_bool(&philo->thread_ready))
		;
}

void	safe_writting(t_philo *philo, t_mutsec opcode)
{
	if (philo->data->dead == true)
		return ;
	safe_mutex(&philo->data->write_lock, LOCK);
	philo->time = get_time() - philo->data->start_time;
	if ( opcode == FORK)
		printf("%ld %d has taken a fork\n", philo->time, philo->id);
	else if ( opcode == EAT)
		printf("%ld %d is eating\n", philo->time, philo->id);
	else if ( opcode == SLEEP)
		printf("%ld %d is spleeping\n", philo->time, philo->id);
	else if ( opcode == THINK)		
		printf("%ld %d is thinking\n", philo->time, philo->id);
	else if ( opcode == DIE)
		printf("%ld %d died\n", philo->time, philo->id);
	safe_mutex(&philo->data->write_lock, UNLOCK);	
}

void	eating(t_philo *philo)
{
	safe_mutex(&philo->first_fork->fork, LOCK);
	safe_writting(philo, FORK);
	safe_mutex(&philo->second_fork->fork, LOCK);
	safe_writting(philo, FORK);
	safe_writting(philo, EAT);
	usleep(philo->data->time_to_eat);
	safe_mutex(&philo->meal_lock, LOCK);
	philo->meal_count += 1;
	philo->time_lst_meal = get_time();
	safe_mutex(&philo->meal_lock, UNLOCK);
	safe_mutex(&philo->second_fork->fork, UNLOCK);
	safe_mutex(&philo->first_fork->fork, UNLOCK);
}

void	which_action(t_philo *philo, t_mutsec opcode)
{
	if (opcode == SLEEP)
	{
		safe_writting(philo, SLEEP);
		usleep(philo->data->time_to_sleep);
	}
	if (opcode == THINK)
	{
		safe_writting(philo, THINK);
		usleep(100);
	}

}

void*	what_to_do(void *data)
{
	t_philo *philo;
	philo = data;
	
	wait_for_threads(philo);
	if (philo->id % 2 == 0)
		usleep(10);
	int i =-1;
	// while (philo->data->dead == false)
	while (++i < 10)
	{
		if (philo->data->nb_philos % 2 == 0)
		{
			if (philo->id == 1)
				usleep(100);
		}
		if (philo->data->dead == true)
			break;
		eating(philo);
		which_action(philo, SLEEP);
		which_action(philo, THINK);		
	}
	return NULL;
}


void*	check_dead(void *dato)
{
	t_data	*data;
	int		i;
	
	data = dato;
	while (1)
	{
		i =-1;
		while(++i < data->nb_philos)
		{
			safe_mutex(&data->philo[i].meal_lock, LOCK);
			if ((get_time() - data->philo->time_lst_meal ) > data->philo->data->time_to_die)
			{
				printf("TETSTETSTETSTETST\n");
				safe_writting(data->philo, DIE);
				safe_mutex(&data->philo[i].dead_lock, LOCK);
				data->dead = true;
				safe_mutex(&data->philo[i].dead_lock, UNLOCK);
				return NULL;
			}			
			safe_mutex(&data->philo[i].meal_lock, UNLOCK);
			return NULL;
		}	
		usleep(100);
	}
	return NULL;
}

int	a_table(t_data *data)
{
	int	i;
	
	i = -1;
	if (data->nb_philos == 1)
		printf("\n");//fonction a faire;
	else
	{
		data->start_time = get_time();
		while(++i < data->nb_philos)
		{
			if (safe_thread(&data->philo[i].threads_ids, what_to_do, &data->philo[i], CREATE))
				return (1);
			set_bool(data, i, true);
		}
		i = -1;
		while (++i < data->nb_philos)
		{
			if (safe_thread(&data->philo[i].threads_ids, what_to_do, NULL, JOIN))
				return (1);
		}
		if (safe_thread(&data->assas, check_dead, &data, CREATE))
			return (3);
		if (safe_thread(&data->assas, check_dead, &data, JOIN))
			return (4);
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


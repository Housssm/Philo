/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:26:41 by hoel-har          #+#    #+#             */
/*   Updated: 2026/04/02 19:52:33 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



// erreur :

// should die is ok should not die all false 
// - uneven numbers - one should die  quelques erreurs 
// - testing even number they should not die 50 / 50 
// - testing even number overkill they should not die MAJORITY FAULSE
// - testing uneven number should not die 1/3
// - testing uneven number should not die overkill MAJORITY FALSE

void	free_struct(t_data *data)
{
	int	i;
	
	i = -1;
	if (data->philo != NULL)
	{	
		while(++i < data->nb_philos)
		{
			safe_mutex(&data->philo[i].meal_lock, DESTROY);
			safe_mutex(&data->philo[i].dead_lock, DESTROY);
		}
		free(data->philo);
	}
	i = -1;
	if (data->forks != NULL)
	{
		while (++i<data->nb_philos)
			safe_mutex(&data->forks[i].fork, DESTROY);
		free(data->forks);
	}
	safe_mutex(&data->time_lock, DESTROY);
	safe_mutex(&data->write_lock, DESTROY);
	safe_mutex(&data->table_lock, DESTROY);
	safe_mutex(&data->count_lock, DESTROY);
}

static bool	is_dead(t_data *data)
{
	bool	result;

	safe_mutex(&data->count_lock, LOCK);
	result = data->dead;
	safe_mutex(&data->count_lock, UNLOCK);
	return (result);
}

static bool	is_full(t_data *data)
{
	bool	result;

	safe_mutex(&data->time_lock, LOCK);
	result = data->full;
	safe_mutex(&data->time_lock, UNLOCK);
	return (result);
}

static void	set_dead(t_data *data, bool value)
{
	safe_mutex(&data->time_lock, LOCK);
	data->dead = value;
	safe_mutex(&data->time_lock, UNLOCK);
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
}


// //TIME 

long get_time(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL))
		return(0);
	return ((time.tv_sec * (long)1000) + (time.tv_usec / 1000));
}

static void precise_sleep(t_data *data, long ms)
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


void	safe_writting(t_philo *philo, t_mutsec opcode)
{
	long	time;
	
	safe_mutex(&philo->data->time_lock, LOCK);
	if (philo->data->dead && opcode != DIE)
		return (safe_mutex(&philo->data->time_lock, UNLOCK), (void)0);
	time = get_time() - philo->data->start_time;
	// if (philo->data->dead && opcode != DIE)
	// return (safe_mutex(&philo->data->time_lock, UNLOCK), (void)0 );
	safe_mutex(&philo->data->write_lock, LOCK);
	philo->time = get_time() - philo->data->start_time;
	if ( opcode == FORK)
		printf("%ld %d has taken a fork\n", time, philo->id);
	else if ( opcode == EAT)
		printf("%ld %d is eating\n", time, philo->id);
	else if ( opcode == SLEEP)
		printf("%ld %d is sleeping\n", time, philo->id);
	else if ( opcode == THINK)		
		printf("%ld %d is thinking\n", time, philo->id);
	else if ( opcode == DIE)
		printf("%ld %d died\n", time, philo->id);
	safe_mutex(&philo->data->write_lock, UNLOCK);
	safe_mutex(&philo->data->time_lock, UNLOCK);
}

void	eating(t_philo *philo)
{
	safe_mutex(&philo->first_fork->fork, LOCK);
	safe_writting(philo, FORK);
	if (is_dead(philo->data))
	{
		safe_mutex(&philo->first_fork->fork, UNLOCK);
		return ;
	}
	safe_mutex(&philo->second_fork->fork, LOCK);
	safe_writting(philo, FORK);
	
	safe_mutex(&philo->meal_lock, LOCK);
	philo->meal_count += 1;
	philo->time_lst_meal = get_time();
	safe_mutex(&philo->meal_lock, UNLOCK);
	safe_writting(philo, EAT);
	precise_sleep(philo->data, philo->data->time_to_eat);
	safe_mutex(&philo->second_fork->fork, UNLOCK);
	safe_mutex(&philo->first_fork->fork, UNLOCK);
}

void	which_action(t_philo *philo, t_mutsec opcode)
{
	if (opcode == SLEEP)
	{
		safe_writting(philo, SLEEP);
		precise_sleep(philo->data, philo->data->time_to_sleep);
	}
	if (opcode == THINK)
	{
		safe_writting(philo, THINK);
		usleep(10);
	}
}

static void	wait_start(t_data *data)
{
	while (1)
	{
		safe_mutex(&data->table_lock, LOCK);
		if (data->time_starded)
		{
			safe_mutex(&data->table_lock, UNLOCK);
			return ;
		}
		safe_mutex(&data->table_lock, UNLOCK);
		usleep(10);
	}
}

void*	what_to_do(void *data)
{
	t_philo *philo;
	
	philo = data;
	wait_start(philo->data);
	if (philo->id % 2 == 0)
		usleep(100);
	while (!is_dead(philo->data))
	{
		if (philo->data->nb_philos % 2 != 0 && philo->id == 1)
			usleep(100);
		eating(philo);
		if (is_dead(philo->data) || is_full(philo->data))
			break;
		which_action(philo, SLEEP);
		which_action(philo, THINK);		
	}
	return NULL;
}


static bool	all_philos_full(t_data *data)
{
	int		i;
	int		full_count;
	long	meal_count;

	if (data->must_eat == -1)
		return (false);
	full_count = 0;
	i = -1;
	while (++i < data->nb_philos)
	{
		safe_mutex(&data->philo[i].meal_lock, LOCK);
		meal_count = data->philo[i].meal_count;
		safe_mutex(&data->philo[i].meal_lock, UNLOCK);
		if (meal_count >= data->must_eat)
			full_count++;
	}
	return (full_count == data->nb_philos);
}

static void	mark_full_and_stop(t_data *data)
{
	safe_mutex(&data->count_lock, LOCK);
	data->full = true;
	safe_mutex(&data->count_lock, UNLOCK);
	set_dead(data, true);
}

static bool	check_one_death(t_data *data, int i)
{
	long	last_meal;

	safe_mutex(&data->philo[i].meal_lock, LOCK);
	last_meal = data->philo[i].time_lst_meal;
	safe_mutex(&data->philo[i].meal_lock, UNLOCK);
	if ((get_time() - last_meal) <= data->time_to_die)
		return (false);
	safe_mutex(&data->time_lock, LOCK);
	if (!data->dead)
	{
		data->dead = true;
		safe_mutex(&data->write_lock, LOCK);
		printf("%ld %d died\n", get_time() - data->start_time, data->philo[i].id);
		safe_mutex(&data->write_lock, UNLOCK);
	}
	safe_mutex(&data->time_lock, UNLOCK);
	return (true);
}

void*	check_dead(void *dato)
{
	t_data	*data;
	int		i;

	data = (t_data *)dato;
	wait_start(data);
	while (!is_dead(data))
	{
		if (all_philos_full(data))
			return (mark_full_and_stop(data), NULL);
		i = -1;
		while (++i < data->nb_philos && !is_dead(data))
			if (check_one_death(data, i))
				return (NULL);
		usleep(1000);
	}
	return (NULL);
}

int	lonely(t_data *data)
{
	data->start_time = get_time();
	data->philo[0].time_lst_meal = data->start_time;
	safe_writting(&data->philo[0], FORK);
	precise_sleep(data, data->time_to_die);
	set_dead(data, true);
	safe_writting(&data->philo[0], DIE);
	return (0);
}

int	a_table(t_data *data)
{
	int	i;

	if (data->nb_philos == 1)
		return (lonely(data));
	data->start_time = get_time();
	i = -1;
	while (++i < data->nb_philos)
		data->philo[i].time_lst_meal = data->start_time;
	i = -1;
	while (++i < data->nb_philos)
		if (safe_thread(&data->philo[i].threads_ids,
				what_to_do, &data->philo[i], CREATE))
			return (1);
	if (safe_thread(&data->assas, check_dead, data, CREATE))
		return (3);
	safe_mutex(&data->table_lock, LOCK);
	data->time_starded = true;
	safe_mutex(&data->table_lock, UNLOCK);
	i = -1;
	while (++i < data->nb_philos)
		if (safe_thread(&data->philo[i].threads_ids, NULL, NULL, JOIN))
			return (1);
	if (safe_thread(&data->assas, NULL, NULL, JOIN))
		return (4);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	
	memset(&data, 0, sizeof(data));
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

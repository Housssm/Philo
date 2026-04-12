/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-har <hoel-har@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 09:26:41 by hoel-har          #+#    #+#             */
/*   Updated: 2026/04/12 16:40:18 by hoel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	memset(&data, 0, sizeof(data));
	if (ac == 5 || ac == 6)
	{
		if (check_and_init(ac, av, &data))
			return (free_struct(&data), 1);
		if (a_table(&data))
			return (free_struct(&data), 1);
	}
	else
		return (printf("Invalid number of argument\n"), 1);
	free_struct(&data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:40:56 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/20 12:16:33 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_threads(t_data_storage *data)
{
	free(data->philos);
	free(data->forks);
}

int	main(int argc, char **argv)
{
	t_data_storage	data_storage;
	
	if (input_check(argc, argv) == -1)
		return (-1);
	if (load_input(argc, argv, &data_storage.times) == -1)
		return (-1);
	start_threads(&data_storage);
	//free_threads(&philo_data);
	// if(philo_data->philos)
	// free(philo_data->philos);
	// free(philo_data->forks);
	// free(philo_data);
	return (1);
}

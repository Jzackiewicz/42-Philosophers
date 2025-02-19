/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:40:56 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/18 17:15:47 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo_data(t_input_args inputs, t_philo_data *philo_data)
{
	philo_data->args = inputs;
	if (gettimeofday(&philo_data->start_time, NULL) == -1)
		return (-1);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo_data	philo_data;
	t_input_args	input_args;
	
	if (input_check(argc, argv) == -1)
		return (-1);
	if (load_input(argc, argv, &input_args) == -1)
		return (-1);
	if (init_philo_data(input_args, &philo_data) == -1)
		return (-1);

	start_threads(&philo_data);
	// if(philo_data->philos)
	// free(philo_data->philos);
	// free(philo_data->forks);
	// free(philo_data);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:40:56 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/27 17:23:03 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_data_storage *data)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	if (data->forks)
	{
		while (i < data->times.philos_num)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (data->monitor_data)
	{
		pthread_mutex_lock(&data->monitor_data->monitor_mutex);
		pthread_mutex_unlock(&data->monitor_data->monitor_mutex);
		pthread_mutex_destroy(&data->monitor_data->monitor_mutex);
		pthread_mutex_lock(&data->monitor_data->write_mutex);
		pthread_mutex_unlock(&data->monitor_data->write_mutex);
		pthread_mutex_destroy(&data->monitor_data->write_mutex);
		free(data->monitor_data);
	}
	free(data->philos);
}

int	init_philos(t_data_storage *data)
{
	int	i;

	data->philos = (t_philo_data *)malloc(sizeof(t_philo_data)
			* data->times.philos_num);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->times.philos_num);
	if (!data->philos || !data->forks)
		return (-1);
	i = 0;
	data->end_flag = false;
	while (i < data->times.philos_num)
	{
		data->philos[i].id = i;
		data->philos[i].data_storage = data;
		data->philos[i].last_meal_timestamp = data->times.start_time;
		data->philos[i].meals_num = 0;
		data->philos[i].l_fork = &data->forks[i];
		if (i + 1 >= data->times.philos_num)
			data->philos[i].r_fork = &data->forks[0];
		else
			data->philos[i].r_fork = &data->forks[i + 1];
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data_storage	data_storage;

	if (input_check(argc, argv) == -1)
		return (cleanup(&data_storage), -1);
	if (load_input(argc, argv, &(data_storage.times)) == -1)
		return (cleanup(&data_storage), -1);
	if (init_philos(&data_storage) == -1)
		return (cleanup(&data_storage), -1);
	if (start_monitor(&data_storage) == -1)
		return (cleanup(&data_storage), -1);
	if (start_threads(&data_storage) == -1)
		return (cleanup(&data_storage), -1);
	cleanup(&data_storage);
	return (1);
}

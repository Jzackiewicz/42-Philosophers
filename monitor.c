/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:30:25 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/27 16:47:21 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_status(t_data_storage *data)
{
	pthread_mutex_lock(&data->monitor_data->monitor_mutex);
	if (data->end_flag)
	{
		pthread_mutex_unlock(&data->monitor_data->monitor_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&data->monitor_data->monitor_mutex);
	return (1);
}

static bool	are_philos_fed(t_data_storage *data)
{
	int	i;

	i = 0;
	while (i < data->times.philos_num)
	{
		if (data->philos[i].meals_num <= data->times.num_of_iter - 1
			|| data->times.num_of_iter == -1)
			return (false);
		i++;
	}
	return (true);
}

static bool	is_philo_dead(t_data_storage *data)
{
	int	i;

	i = 0;
	while (i < data->times.philos_num)
	{
		if (get_time()
			- data->philos[i].last_meal_timestamp > data->times.time2die)
		{
			dying(&data->philos[i]);
			return (true);
		}
		i++;
	}
	return (false);
}

static void	*routine(void *arg)
{
	t_data_storage	*data;

	data = (t_data_storage *)arg;
	ft_usleep(1);
	if (check_status(data) == -1)
		return (NULL);
	while (!data->end_flag)
	{
		pthread_mutex_lock(&data->monitor_data->monitor_mutex);
		if (is_philo_dead(data))
			data->end_flag = true;
		if (are_philos_fed(data))
			data->end_flag = true;
		pthread_mutex_unlock(&data->monitor_data->monitor_mutex);
	}
	return (NULL);
}

int	start_monitor(t_data_storage *data)
{
	data->monitor_data = (t_monitor_data *)malloc(sizeof(t_monitor_data));
	if (!data->monitor_data)
		return (-1);
	if (pthread_mutex_init(&data->monitor_data->monitor_mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->monitor_data->write_mutex, NULL) != 0)
		return (-1);
	if (pthread_create(&data->monitor_data->monitor, NULL, &routine, data) != 0)
		return (-1);
	pthread_detach(data->monitor_data->monitor);
	return (1);
}

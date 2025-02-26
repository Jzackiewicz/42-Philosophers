/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:30:25 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/26 16:48:36 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{
	t_data_storage	*data;
	int				i;

	data = (t_data_storage *)arg;
	while (!data->death)
	{
		pthread_mutex_lock(&data->monitor_data->monitor_mutex);
		i = 0;
		while (i < data->times.philos_num)
		{
			if (get_time()
				- data->philos[i].last_meal_timestamp > data->times.time2die)
			{
				data->death = true;
				dying(&data->philos[i]);
				pthread_mutex_unlock(&data->monitor_data->monitor_mutex);
				return (NULL);
			}
			if (data->philos[i].meals_num >= data->times.num_of_iter
				&& data->times.num_of_iter != -1)
			{
				data->philos_fed++;
				pthread_mutex_unlock(&data->monitor_data->monitor_mutex);
				return (NULL);
			}
			i++;
		}
		pthread_mutex_unlock(&data->monitor_data->monitor_mutex);
		ft_usleep(1);
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
	if (pthread_create(&data->monitor_data->monitor, NULL, routine, data) != 0)
		return (-1);
	pthread_detach(data->monitor_data->monitor);
	return (1);
}

int	check_status(t_data_storage *data)
{
	pthread_mutex_lock(&data->monitor_data->monitor_mutex);
	if (data->death || data->philos_fed >= data->times.philos_num)
	{
		pthread_mutex_unlock(&data->monitor_data->monitor_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&data->monitor_data->monitor_mutex);
	return (1);
}
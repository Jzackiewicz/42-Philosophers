/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:48:49 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/20 16:54:39 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo_data	*philo_data;
	int				i;
	philo_data = (t_philo_data *)arg;
	i = 0;
	while (i < philo_data->data_storage->times.num_of_iter)
	{		
		thinking(philo_data);
		eating(philo_data);
		i++;
	}
	// printf("mutex: %d\n", pthread_mutex_lock(&philo_data->data_storage->forks[0]));
	// printf("mutex: %d\n", pthread_mutex_lock(&philo_data->data_storage->forks[0]));
	//pthread_mutex_unlock(&philo_data->data_storage->forks[0]);
	printf("ending thread\n");
	return (NULL);
}

int	assign_values(t_philo_data *philo_data, int i, t_data_storage *data)
{
	data->philos[i].id = i;
	data->philos[i].data_storage = data;
}

int	start_threads(t_data_storage *data)
{
	int	i;

	data->philos = (t_philo_data *)malloc(sizeof(t_philo_data)
			* data->times.philos_num);
	data->forks = (t_fork_data *)malloc(sizeof(t_fork_data)
			* data->times.philos_num);
	if (!data->philos || !data->forks)
		return (-1);
	i = -1;
	while (++i < data->times.philos_num)
	{
		assign_values
		if (pthread_create(&data->philos[i].philo, NULL, &routine,
				&data->philos[i]) != 0)
			return (-1);
		if (pthread_mutex_init(&data->forks[i].fork, NULL) != 0)
			return (-1);
		data->forks[i].is_locked = false;
	}
	i = -1;
	while (++i < data->times.philos_num)
	{
		if (pthread_join(data->philos[i].philo, NULL) != 0)
			return (-1);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:48:49 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/25 17:05:16 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo_data	*philo_data;
	int				i;
	
	philo_data = (t_philo_data *)arg;
	i = 0;
	while (!philo_data->data_storage->death)
	{
		thinking(philo_data);
		eating(philo_data);
		sleeping(philo_data);
		ft_usleep(1);
	}
	return (NULL);
}

int	start_threads(t_data_storage *data)
{
	int	i;

	i = -1;
	while (++i < data->times.philos_num)
	{
		if (pthread_create(&data->philos[i].philo, NULL, &routine,
				&data->philos[i]) != 0)
			return (-1);
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (-1);
	}
	i = -1;
	while (++i < data->times.philos_num)
	{
		if (pthread_join(data->philos[i].philo, NULL) != 0)
			return (-1);
	}
	return (1);
}

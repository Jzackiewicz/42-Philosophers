/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:48:49 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/20 12:17:43 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_data_storage	data;

	data = *(t_data_storage *)arg;
	printf("%d\n", data.times.time2die);
	printf("starting thread\n");
	sleep(3);
	printf("ending thread\n");
	return (NULL);
}

int	start_threads(t_data_storage *data)
{
	int			i;

	data->philos = (t_philo_data *)malloc(sizeof(t_philo_data)
			*  data->times.philos_num);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			*  data->times.philos_num);
	if (!data->philos || !data->forks)
		return (-1);
	i = -1;
	while (++i <  data->times.philos_num)
	{
		if (pthread_create(&data->philos[i].philo, NULL, &routine, data) != 0)
			return (-1);
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (-1);
		data->philos->id = i;
	}
	i = -1;
	while (++i <  data->times.philos_num)
	{
		if (pthread_join(data->philos[i].philo, NULL) != 0)
			return (-1);
	}
	return (1);
}

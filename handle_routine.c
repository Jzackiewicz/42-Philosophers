/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:48:49 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/18 17:15:59 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*routine(void *arg)
{	
	(void) arg;
	printf("starting thread\n");
	sleep(3);
	printf("ending thread\n");
	return (NULL);
}

int	start_threads(t_philo_data *data)
{
	int	i;
	t_input_args args;

	args = data->args;
	data->philos = (pthread_t *)malloc(sizeof(pthread_t) * args.philos_num);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * args.philos_num);
	if (!data->philos || !data->forks)
        return (-1);
	i = 0;
	while (i < args.philos_num)
	{
		if (pthread_create(data->philos + i, NULL, &routine, NULL) != 0)
			return (-1);
		i++;
	}
	i = 0;
	while (i < args.philos_num)
	{
		if (pthread_join(data->philos[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (1);
}
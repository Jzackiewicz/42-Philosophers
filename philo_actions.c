/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:46:00 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/26 16:13:06 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo_data *philo_data)
{
	printf("%ld %d is thinking\n", get_time()
		- philo_data->data_storage->times.start_time, philo_data->id);
}

void	sleeping(t_philo_data *philo_data)
{
	printf("%ld %d is sleeping\n", get_time()
		- philo_data->data_storage->times.start_time, philo_data->id);
	ft_usleep(philo_data->data_storage->times.time2sleep);
}

void	dying(t_philo_data *philo_data)
{
	printf("%ld %d died\n", get_time()
		- philo_data->data_storage->times.start_time, philo_data->id);
}
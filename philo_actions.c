/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:46:00 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/25 15:23:08 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo_data *philo_data)
{
	printf("%ld %d is thinking\n", get_time()
		- philo_data->data_storage->times.start_time, philo_data->id);
}

static void	take_fork(pthread_mutex_t *fork, t_philo_data *philo_data)
{
	pthread_mutex_lock(fork);
	printf("%ld %d has taken a fork\n", get_time()
	- philo_data->data_storage->times.start_time, philo_data->id);
}

void	eating(t_philo_data *philo_data)
{
	take_fork(philo_data->l_fork, philo_data);
	take_fork(philo_data->r_fork, philo_data);
	printf("%ld %d is eating\n", get_time()
	- philo_data->data_storage->times.start_time, philo_data->id);
	ft_usleep(philo_data->data_storage->times.time2eat);
	philo_data->last_meal_timestamp = get_time();
	pthread_mutex_unlock(philo_data->l_fork);
	pthread_mutex_unlock(philo_data->r_fork);
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
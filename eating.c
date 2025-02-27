/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:44:10 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/27 16:39:49 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo_data *philo_data, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	t_data_storage	*data;

	data = philo_data->data_storage;
	if (check_status(data) == -1)
		return ;
	pthread_mutex_lock(first_fork);
	if (check_status(data) == -1)
	{
		pthread_mutex_unlock(first_fork);
		return ;
	}
	printf("%ld %d has taken a fork\n", get_time()
		- philo_data->data_storage->times.start_time, philo_data->id);
	pthread_mutex_lock(second_fork);
	if (check_status(data) == -1)
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return ;
	}
	printf("%ld %d has taken a fork\n", get_time()
		- philo_data->data_storage->times.start_time, philo_data->id);
}

static void	leave_forks(pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}

static void	eat_with_forks(t_philo_data *philo_data,
		pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	take_forks(philo_data, first_fork, second_fork);
	if (check_status(philo_data->data_storage) == -1)
		return ;
	pthread_mutex_lock(&philo_data->data_storage->monitor_data->write_mutex);
	printf("%ld %d is eating\n", get_time()
		- philo_data->data_storage->times.start_time, philo_data->id);
	pthread_mutex_unlock(&philo_data->data_storage->monitor_data->write_mutex);
	ft_usleep(philo_data->data_storage->times.time2eat);
	pthread_mutex_lock(&philo_data->data_storage->monitor_data->monitor_mutex);
	philo_data->last_meal_timestamp = get_time();
	philo_data->meals_num++;
	pthread_mutex_unlock(
		&philo_data->data_storage->monitor_data->monitor_mutex);
	leave_forks(second_fork, first_fork);
}

void	eating(t_philo_data *philo_data)
{
	if (philo_data->id % 2 == 0)
		eat_with_forks(philo_data, philo_data->r_fork, philo_data->l_fork);
	else
		eat_with_forks(philo_data, philo_data->l_fork, philo_data->r_fork);
}

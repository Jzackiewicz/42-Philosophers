/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:46:00 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/26 15:43:02 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo_data *philo_data)
{
	printf("%ld %d is thinking\n", get_time()
		- philo_data->data_storage->times.start_time, philo_data->id);
}

void	take_forks(t_philo_data *philo_data, pthread_mutex_t first_fork, pthread_mutex_t second_fork)
{
	t_data_storage *data;

	data = philo_data->data_storage;
	if (check_status(data) == -1)
		return ;
	pthread_mutex_lock(&first_fork);
	if (check_status(data) == -1)
	{
		pthread_mutex_unlock(&first_fork);
		return ;
	}
	printf("%ld %d has taken a fork\n", get_time()
			- philo_data->data_storage->times.start_time, philo_data->id);
	pthread_mutex_lock(&second_fork);
	if (check_status(data) == -1)
	{
		pthread_mutex_unlock(&first_fork);
		pthread_mutex_unlock(&second_fork);
		return ;
	}
	printf("%ld %d has taken a fork\n", get_time()
			- philo_data->data_storage->times.start_time, philo_data->id);
}

void	leave_forks(pthread_mutex_t first_fork, pthread_mutex_t second_fork)
{
	pthread_mutex_unlock(&first_fork);
	pthread_mutex_unlock(&second_fork);
}

void	eating(t_philo_data *philo_data)
{
	if (philo_data->id % 2 == 0) // 🔥 Parzyste ID: najpierw prawy widelec
	{
		take_forks(philo_data, *philo_data->r_fork, *philo_data->l_fork);
		printf("%ld %d is eating\n", get_time()
			- philo_data->data_storage->times.start_time, philo_data->id);
		ft_usleep(philo_data->data_storage->times.time2eat);
		philo_data->last_meal_timestamp = get_time();
		leave_forks(*philo_data->l_fork, *philo_data->r_fork);
	}
	else // 🔥 Nieparzyste ID: najpierw lewy widelec
	{
		take_forks(philo_data, *philo_data->l_fork, *philo_data->r_fork);
		printf("%ld %d is eating\n", get_time()
			- philo_data->data_storage->times.start_time, philo_data->id);
		ft_usleep(philo_data->data_storage->times.time2eat);
		philo_data->last_meal_timestamp = get_time();
		leave_forks(*philo_data->r_fork, *philo_data->l_fork);
	}
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
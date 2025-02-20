/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:46:00 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/20 16:47:09 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo_data *philo_data)
{
	printf("%ld %d is thinking\n", get_time()
		- philo_data->data_storage->times.start_time, philo_data->id);
}

int	eating(t_philo_data *philo_data)
{
	printf("%ld %d is eating\n", get_time()
		- philo_data->data_storage->times.start_time, philo_data->id);
	
	if (!philo_data->r_fork->is_locked && !philo_data->l_fork->is_locked)
	{
		philo_data->r_fork->is_locked = true;
		philo_data->l_fork->is_locked = true;
		ft_usleep(philo_data->data_storage->times.time2die);
	}
	else
		return (0);
	
	return (1);
}
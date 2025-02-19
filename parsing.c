/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:56:21 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/18 16:13:51 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *nptr)
{
	int	output;
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	output = 0;
	while (nptr[i] == ' ' || nptr[i] == '\f' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		if (nptr[i + 1] == '-' || nptr[i + 1] == '+')
			return (sign * output);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		output = 10 * output + (nptr[i] - '0');
		i++;
	}
	return (sign * output);
}

int	load_input(int argc, char **argv, t_input_args *data)
{
	// data = (t_input_args *)malloc(sizeof(t_input_args));
	if (!data)
		return (-1);
	data->philos_num = ft_atoi(argv[1]);
	data->time2die = ft_atoi(argv[2]);
	data->time2eat = ft_atoi(argv[3]);
	data->time2sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_of_iter = ft_atoi(argv[5]);
	else
		data->num_of_iter = -1;
	return (1);
}
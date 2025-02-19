/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:03:33 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/18 10:08:31 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check4overflow(char *nbr)
{
	char	*str_int_limit;
	int		int_limit_strlen;
	int		nbr_strlen;

	int_limit_strlen = 10;
	nbr_strlen = ft_strlen(nbr);
	if (nbr_strlen > int_limit_strlen)
		return (-1);
	else if (nbr_strlen == int_limit_strlen)
	{
		str_int_limit = "2147483647";
		if (ft_strncmp(nbr, str_int_limit, int_limit_strlen) > 0)
			return (-1);
	}
	return (1);
}

static int	check_args_content(char **argv)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (argv[i])
	{
		if (check4overflow(argv[i]) == -1)
		{
			printf("Invalid input!\n");
			return (-1);
		}
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Invalid input!\n");
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_args_num(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error!\nWrong number of arguments!\n./philo "
			"<num_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> "
			"[num_of_iterations]\n");
		return (-1);
	}
	return (1);
}

int	input_check(int argc, char **argv)
{
	if (check_args_num(argc) == -1 || check_args_content(argv) == -1)
		return (-1);
	return (1);
}

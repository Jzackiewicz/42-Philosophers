/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:41:03 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/18 17:15:47 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_input_args
{
	int				philos_num;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	int				num_of_iter;
}					t_input_args;

typedef struct s_philo_data
{
	struct timeval	start_time;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	t_input_args	args;
}					t_philo_data;


//					utils
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

//					error_handling
int					input_check(int argc, char **argv);

//					parsing
int					load_input(int argc, char **argv, t_input_args *data);

int					start_threads(t_philo_data *data);
#endif
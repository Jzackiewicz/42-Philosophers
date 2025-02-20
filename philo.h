/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:41:03 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/20 12:44:37 by jzackiew         ###   ########.fr       */
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

typedef struct s_set_times
{
	int				philos_num;
	int				time2die;
	int				time2eat;
	int				time2sleep;
	int				num_of_iter;
}					t_set_times;

typedef struct		s_philo_data
{
	pthread_t		philo;
	int				id;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philo_data;

typedef struct s_data_storage
{
	t_philo_data	*philos;
	pthread_mutex_t	*forks;
	t_set_times		times;
}					t_data_storage;

//					utils
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					get_time(void);
int					ft_usleep(int time);
void				ft_debug(void);

//					error_handling
int					input_check(int argc, char **argv);

//					parsing
int					load_input(int argc, char **argv, t_set_times *data);

int					start_threads(t_data_storage *data);
#endif
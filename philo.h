/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:41:03 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/25 15:22:45 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h> 

typedef struct s_set_times
{
	int						philos_num;
	int						num_of_iter;
	long int				time2die;
	long int				time2eat;
	long int				time2sleep;
	long int				start_time;
}							t_set_times;

typedef struct s_philo_data
{
	pthread_t				philo;
	int						id;
	pthread_mutex_t			*r_fork;
	pthread_mutex_t			*l_fork;
	long int				last_meal_timestamp;
	struct s_data_storage	*data_storage;
	int						meals_num;
}							t_philo_data;

typedef struct s_monitor_data
{
	pthread_t				monitor;
	pthread_mutex_t			monitor_mutex;
}							t_monitor_data;

typedef struct s_data_storage
{
	t_philo_data			*philos;
	pthread_mutex_t			*forks;
	t_monitor_data			*monitor_data;
	t_set_times				times;
	bool					death;
	bool					all_ate;
}							t_data_storage;

//							utils
size_t						ft_strlen(const char *s);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
long int					get_time(void);
int							ft_usleep(long int time);
void						ft_debug(void);

//							error_handling
int							input_check(int argc, char **argv);

//							parsing
int							load_input(int argc, char **argv,
								t_set_times *data);

//							philo_actions
void						thinking(t_philo_data *philo_data);
void						eating(t_philo_data *philo_data);
void						sleeping(t_philo_data *philo_data);
void						dying(t_philo_data *philo_data);
int							start_threads(t_data_storage *data);

//							monitor
int							start_monitor(t_data_storage *data);
#endif
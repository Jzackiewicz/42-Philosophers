/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:41:03 by jzackiew          #+#    #+#             */
/*   Updated: 2025/02/20 14:50:57 by jzackiew         ###   ########.fr       */
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
	struct s_fork_data		*r_fork;
	struct s_fork_data		*l_fork;
	struct s_data_storage	*data_storage;
}							t_philo_data;

typedef struct s_fork_data
{
	pthread_mutex_t			fork;
	bool					is_locked;
}							t_fork_data;

typedef struct s_data_storage
{
	t_philo_data			*philos;
	t_fork_data				*forks;
	t_set_times				times;
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
int							eating(t_philo_data *philo_data);

int							start_threads(t_data_storage *data);
#endif
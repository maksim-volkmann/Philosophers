/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:01:13 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/14 17:19:20 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://nafuka11.github.io/philosophers-visualizer/

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>


// typedef struct s_philo
// {
// 	int				id;
// 	int				is_eating;
// 	uint64_t		last_meal_time;
// 	uint64_t		limit_time_to_die;
// 	pthread_t		thread_id;
// 	struct s_data	*data;
// 	pthread_mutex_t	mutex;
// 	pthread_mutex_t	*left_fork;
// 	pthread_mutex_t	*right_fork;
// }	t_philo;

// typedef struct s_data
// {
// 	int				num_philos;
// 	uint64_t		time_to_die;
// 	uint64_t		time_to_eat;
// 	uint64_t		time_to_sleep;
// 	int				all_ate;
// 	pthread_mutex_t	write_lock;
// 	pthread_mutex_t	*forks;
// 	t_philo			*philos;
// }	t_data;



struct s_data;  // Forward declaration



typedef struct s_philo
{
	int                 id;
	int                 eat_count;
	int                 is_eating;
	struct s_data		*data;
	uint64_t            last_meal_time;
	pthread_t           thread_id;
	pthread_mutex_t     *left_fork;
	pthread_mutex_t     *right_fork;

}	t_philo;

// ./philo 5 450 200 200 1
typedef struct s_data
{
	int				numb_of_philos;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				number_of_meals;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_mutex_t	write;
	bool			died;
	pthread_t		monitor_thread;
	pthread_mutex_t 	fork_mutex;
}	t_data;

// range validator
bool	validate_num_of_philos(int num);
bool	validate_time_to_die(uint64_t num);
bool	validate_time_to_eat(uint64_t num);
bool	validate_time_to_sleep(uint64_t num);
bool	validate_number_of_meals(uint64_t num);

// arugment validator
bool	is_in_int_range(char *str);
bool	is_numeric(char *str);
void	instructions();
int		pre_check(int ac, char **av);

// init values
int		ft_atoi(char *str);
int		init_values(int ac, char **av, t_data *data);

#endif

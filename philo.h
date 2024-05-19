/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:01:13 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/19 12:27:20 by mvolkman         ###   ########.fr       */
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

struct s_data;  // Forward declaration

typedef struct s_philo
{
	int				id;
	int 			eat_count;
	uint64_t 		last_meal_time;
	pthread_t 		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	philo_lock;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				numb_of_philos;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				number_of_meals;
	uint64_t		start_time;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_mutex_t	write;
	bool			died;
	bool			all_ate;
	pthread_t		monitor_thread;
	pthread_t		waiter_thread;
	pthread_mutex_t	all_ate_mutex;
}	t_data;

void	print_log(t_philo *philo, const char *message);
void	single_philo(t_philo *philo);

//routine
bool	check_status(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	*routine(void *arg);

//time management
uint64_t	get_time(void);
void		simulate_action(uint64_t action_time);

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

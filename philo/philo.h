/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:01:13 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/22 17:11:55 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>

struct	s_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	uint64_t		last_meal_time;
	pthread_t		thread_id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	mutex_last_meal;
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
	pthread_mutex_t	died_mutex;
	pthread_mutex_t	all_ate_mutex;
	pthread_t		doctor_thread;
	pthread_t		waiter_thread;
}	t_data;

// cleanup.c
void	clean_last_meal(t_data *data);
void	clean_forks(t_data *data);
void		cleanup(t_data *data);

// actions.c
void		pick_r_fork(t_philo *philo);
void		pick_l_fork(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo, uint64_t time_to_think);

// argument_validator.c
bool		is_in_int_range(char *str);
bool		is_numeric(char *str);
void		instructions(void);
int			pre_check(int ac, char **av);

// create_dinner.c
bool		create_forks(t_data *data);
bool		create_philos(t_data *data);
bool		init_mutexes(t_data *data);
int			dining_init(t_data *data);

// getters_setters.c
bool		get_died(t_data *data);
bool		get_all_ate(t_data *data);
void		set_died(t_data *data, bool value);
void		set_all_ate(t_data *data, bool value);

// init_items.c
int			init_philos(t_data *data);
int			init_forks(t_data *data);

// init_values.c
int			ft_atoi(char *str);
void		additional_init(t_data *data);
int			parse_init_values(int ac, char **av, t_data *data);

// range_validator.c

bool		validate_num_of_philos(int num);
bool		validate_time_to_die(uint64_t num);
bool		validate_time_to_eat(uint64_t num);
bool		validate_time_to_sleep(uint64_t num);
bool		validate_number_of_meals(int num);

// routines.c
void		*routine(void *arg);
void		*doctor(void *arg);
bool		check_all_philos_ate(t_data *data);
void		*waiter(void *arg);

// threads.c
int			start_threads(t_data *data);
void		join_threads(t_data *data);

// time_management.c
uint64_t	get_time(void);
void		simulate_action(uint64_t action_time);

// utils.c
void		print_log(t_philo *philo, const char *message);
bool		check_died_status(t_philo *philo);
bool		check_all_ate_status(t_philo *philo);
void		death_print(t_data *data, int id);

// philo.c
void		single_philo(t_philo *philo);
int			main(int ac, char **av);

#endif

// valgrind --tool=drd --fair-sched=yes ./philo 4 600 200 200 4
// valgrind --tool=helgrind --fair-sched=yes ./philo 2 800 100 100 3

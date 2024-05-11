/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:01:13 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/11 16:47:13 by mvolkman         ###   ########.fr       */
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

typedef struct s_data t_data;  // Forward declaration

// typedef struct s_philo
// {
// 	int                 id;
// 	int                 eat_count;
// 	int                 eating;
// 	uint64_t            last_meal;
// 	pthread_t           thread_id;
// 	struct s_data       *data;
// 	pthread_mutex_t     mutex;
// 	pthread_mutex_t     *left_fork;
// 	pthread_mutex_t     *right_fork;
// }	t_philo;

// ./philo 5 450 200 200 1
typedef struct s_data
{
	int			numb_of_philos;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	int			number_of_meals;
}	t_data;


#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:01:13 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/06 17:21:22 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h> // for sleep function
#include <stdint.h>  // For uint64_t
#include <pthread.h> // fpt threads
#include <stdlib.h>  // Include for malloc and free

typedef struct s_data
{
	pthread_t	*tid;
	int			num_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_of_meals_required;

}	t_data;

typedef struct s_philo
{
	int id;
	t_data *data;
}	t_philo;

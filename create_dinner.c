/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_dinner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:13:44 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/21 12:14:07 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	create_forks(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->numb_of_philos);
	if (!data->forks)
		return (false);
	if (init_forks(data) != 0)
	{
		free(data->forks);
		return (false);
	}
	return (true);
}

bool	create_philos(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->numb_of_philos);
	if (!data->philos)
	{
		free(data->forks);
		return (false);
	}
	init_philos(data);
	return (true);
}

bool	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&data->died_mutex, NULL) != 0
		|| pthread_mutex_init(&data->all_ate_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->write);
		return (false);
	}
	return (true);
}

int	dining_init(t_data *data)
{
	if (!create_forks(data))
		return (1);
	if (!create_philos(data))
		return (1);
	if (!init_mutexes(data))
	{
		free(data->forks);
		free(data->philos);
		return (1);
	}
	return (0);
}

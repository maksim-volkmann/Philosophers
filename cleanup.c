/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:00:54 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/22 17:01:18 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_last_meal(t_data *data)
{
	int	i;

	i = 0;
	if (data->philos)
	{
		while (i < data->numb_of_philos)
		{
			pthread_mutex_destroy(&data->philos[i].mutex_last_meal);
			i++;
		}
		free(data->philos);
		data->philos = NULL;
	}
}

void	clean_forks(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->numb_of_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
}
void	cleanup(t_data *data)
{
	clean_last_meal(data);
	clean_forks(data);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->died_mutex);
	pthread_mutex_destroy(&data->all_ate_mutex);
}

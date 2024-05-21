/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_items.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:15:56 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/21 12:16:08 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numb_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].last_meal_time = get_time();
		data->philos[i].thread_id = 0;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->numb_of_philos];
		if (pthread_mutex_init(&data->philos[i].mutex_last_meal, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->philos[i].mutex_last_meal);
			return (1);
		}
		data->philos[i].data = data;
		i++;
	}
	return (0);
}


int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numb_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

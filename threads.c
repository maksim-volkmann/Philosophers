/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:17:18 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/21 12:17:41 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_data *data)
{
	int	i;

	data->start_time = get_time();
	if (pthread_create(&data->doctor_thread, NULL, doctor, data) != 0)
		return (1);
	if (data->number_of_meals > 0)
	{
		if (pthread_create(&data->waiter_thread, NULL, waiter, data) != 0)
			return (1);
	}
	i = 0;
	while (i < data->numb_of_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL,
				routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_join(data->doctor_thread, NULL);
	if (data->number_of_meals > 0)
		pthread_join(data->waiter_thread, NULL);
	while (i < data->numb_of_philos)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}

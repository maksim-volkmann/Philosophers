/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:04:59 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/21 12:44:04 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numb_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].mutex_last_meal);
		i++;
	}
	free(data->forks);
	free(data->philos);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->died_mutex);
	pthread_mutex_destroy(&data->all_ate_mutex);
}

void	print_log(t_philo *philo, const char *message)
{
	pthread_mutex_lock(&philo->data->write);
	if (!get_died(philo->data) && !get_all_ate(philo->data))
		printf("%llu %d %s\n", get_time() - philo->data->start_time,
			philo->id, message);
	pthread_mutex_unlock(&philo->data->write);
}

bool	check_died_status(t_philo *philo)
{
	bool	result;

	result = get_died(philo->data);
	return (result);
}

bool	check_all_ate_status(t_philo *philo)
{
	bool	result;

	result = get_all_ate(philo->data);
	return (result);
}

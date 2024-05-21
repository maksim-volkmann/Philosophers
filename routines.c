/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:46:05 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/21 12:43:11 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo		*philo;
	uint64_t	time_to_think;

	philo = (t_philo *)arg;
	time_to_think = (philo->data->time_to_eat * 2) - philo->data->time_to_sleep;
	if (philo->data->numb_of_philos == 1)
	{
		single_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(10);
	while (!(check_died_status(philo) || check_all_ate_status(philo)))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo, time_to_think);
	}
	return (NULL);
}

void	*doctor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!(get_died(data) || get_all_ate(data)))
	{
		i = 0;
		while (i < data->numb_of_philos)
		{
			pthread_mutex_lock(&data->philos[i].mutex_last_meal);
			if (get_time() - data->philos[i].last_meal_time > data->time_to_die)
			{
				print_log(&data->philos[i], "died");
				set_died(data, true);
				pthread_mutex_unlock(&data->philos[i].mutex_last_meal);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philos[i].mutex_last_meal);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

bool	check_all_philos_ate(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numb_of_philos)
	{
		pthread_mutex_lock(&data->philos[i].mutex_last_meal);
		if (data->philos[i].eat_count < data->number_of_meals)
		{
			pthread_mutex_unlock(&data->philos[i].mutex_last_meal);
			return (false);
		}
		pthread_mutex_unlock(&data->philos[i].mutex_last_meal);
		i++;
	}
	return (true);
}

void	*waiter(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!(get_died(data) || get_all_ate(data)))
	{
		if (check_all_philos_ate(data))
			set_all_ate(data, true);
		usleep(1000);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 12:24:57 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/19 12:26:14 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_status(t_philo *philo)
{
	bool	result;

	pthread_mutex_lock(&philo->data->all_ate_mutex);
	result = !(philo->data->died || philo->data->all_ate);
	pthread_mutex_unlock(&philo->data->all_ate_mutex);

	return result;
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_log(philo, "has taken a fork");

	pthread_mutex_lock(philo->right_fork);
	print_log(philo, "has taken a fork");

	print_log(philo, "is eating");
	simulate_action(philo->data->time_to_eat);

	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal_time = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->philo_lock);

	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_log(philo, "is sleeping");
	simulate_action(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_log(philo, "is thinking");
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->data->numb_of_philos == 1)
	{
		single_philo(philo);
		return NULL;
	}

	while (check_status(philo))
	{
		if (philo->id % 2 == 0)
			usleep(100);

		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}

	return NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:44:24 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/22 16:27:44 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_r_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_log(philo, "has taken a fork");
}

void	pick_l_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_log(philo, "has taken a fork");
}

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pick_r_fork(philo);
		pick_l_fork(philo);
	}
	else
	{
		pick_l_fork(philo);
		pick_r_fork(philo);
	}
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->mutex_last_meal);
	print_log(philo, "is eating");
	simulate_action(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->mutex_last_meal);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_log(philo, "is sleeping");
	simulate_action(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo, uint64_t time_to_think)
{
	if (philo->data->numb_of_philos % 2 != 0)
	{
		print_log(philo, "is thinking");
		simulate_action(time_to_think);
	}
	else
		print_log(philo, "is thinking");
}

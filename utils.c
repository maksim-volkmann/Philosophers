/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:04:59 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/21 10:11:15 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

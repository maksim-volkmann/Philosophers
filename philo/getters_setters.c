/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:01:35 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/21 10:02:25 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_died(t_data *data)
{
	bool	died;

	pthread_mutex_lock(&data->died_mutex);
	died = data->died;
	pthread_mutex_unlock(&data->died_mutex);
	return (died);
}

bool	get_all_ate(t_data *data)
{
	bool	all_ate;

	pthread_mutex_lock(&data->all_ate_mutex);
	all_ate = data->all_ate;
	pthread_mutex_unlock(&data->all_ate_mutex);
	return (all_ate);
}

void	set_died(t_data *data, bool value)
{
	pthread_mutex_lock(&data->died_mutex);
	data->died = value;
	pthread_mutex_unlock(&data->died_mutex);
}

void	set_all_ate(t_data *data, bool value)
{
	pthread_mutex_lock(&data->all_ate_mutex);
	data->all_ate = value;
	pthread_mutex_unlock(&data->all_ate_mutex);
}

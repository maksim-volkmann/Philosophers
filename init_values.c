/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:19:02 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/11 17:20:20 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	result;

	result = 0;
	while (*str)
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

int	init_values(int ac, char **av, t_data *data)
{
	data->numb_of_philos = ft_atoi(av[1]);
	if (!validate_num_of_philos(data->numb_of_philos))
		return (1);
	data->time_to_die = ft_atoi(av[2]);
	if (!validate_time_to_die(data->time_to_die))
		return (1);
	data->time_to_eat = ft_atoi(av[3]);
	if (!validate_time_to_eat(data->time_to_eat))
		return (1);
	data->time_to_sleep = ft_atoi(av[4]);
	if (!validate_time_to_sleep(data->time_to_sleep))
		return (1);
	if(ac == 6)
	{
		data->number_of_meals = ft_atoi(av[5]);
		if (!validate_number_of_meals(data->number_of_meals))
			return (1);
	}
	else
		data->number_of_meals = -1;
	return (0);
}

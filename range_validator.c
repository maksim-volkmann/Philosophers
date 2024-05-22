/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:45:46 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/22 10:56:02 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	validate_num_of_philos(int num)
{
	if (num <= 0)
	{
		printf("Error: Number of philosophers must be more than 0!\n");
		return (false);
	}
	return (true);
}

bool	validate_time_to_die(uint64_t num)
{
	if (num <= 0)
	{
		printf("Error: Time to die must be more than 0!\n");
		return (false);
	}
	return (true);
}

bool	validate_time_to_eat(uint64_t num)
{
	if (num <= 0)
	{
		printf("Error: Time to eat must be more than 0!\n");
		return (false);
	}
	return (true);
}

bool	validate_time_to_sleep(uint64_t num)
{
	if (num <= 0)
	{
		printf("Error: Time to sleep must be more than 0!\n");
		return (false);
	}
	return (true);
}

bool	validate_number_of_meals(int num)
{
	if (num <= 0)
	{
		printf("Error: Numbers of meals must be more than 0!\n");
		printf("*This argument is optional.\n");
		return (false);
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_validator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:09:17 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/21 12:22:48 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_in_int_range(char *str)
{
	long	result;

	result = 0;
	while (*str)
	{
		result = result * 10 + (*str - '0');
		if (result > INT_MAX)
		{
			printf("One or more numbers are too big!\n");
			return (false);
		}
		str++;
	}
	return (true);
}

bool	is_numeric(char *str)
{
	while(*str)
	{
		if (*str < '0' || *str > '9')
		{
			printf("Non numeric values detected!\n");
			return (false);
		}
		str++;
	}
	return (true);
}

void	instructions()
{
	printf("Incorrect amount of arguments!\n");
	printf("You have to provide: ");
	printf("number_of_philosophers time_to_die time_to_eat time_to_sleep ");
	printf("number_of_times_each_philosopher_must_eat(optional).\n");
	printf("Example1: ./philo 2 450 100 100\n");
	printf("Example2: ./philo 5 800 200 200 3(Optional)\n");
}

int	pre_check(int ac, char **av)
{
	int	i;

	i = 0;
	if(ac != 5 && ac != 6)
	{
		instructions();
		return (1);
	}
	while(++i < ac)
	{
		if(!is_numeric(av[i]))
			return (1);
		if(!is_in_int_range(av[i]))
			return (1);
	}
	return (0);
}

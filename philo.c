/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:29:06 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/11 16:46:53 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	validate_num_of_philos(int num)
{
	if (num <= 0 || num > 200)
	{
		printf("Error: Number of philosophers must be between 1 and 200.\n");
		return (false);
	}
		return (true);
}

bool	validate_time_to_die(uint64_t num)
{
	if(num <= 0)
	{
		printf("Time to die must be more than 0\n");
		return (false);
	}
	return (true);
}

bool	validate_time_to_eat(uint64_t num)
{
	if(num <= 0)
	{
		printf("Time to eat must be more than 0\n");
		return (false);
	}
	return (true);
}

bool	validate_time_to_sleep(uint64_t num)
{
	if(num <= 0)
	{
		printf("Time to sleep must be more than 0\n");
		return (false);
	}
	return (true);
}

bool	validate_number_of_meals(uint64_t num)
{
	if(num <= 0)
	{
		printf("Numbers of meals must be more than 0.\n");
		printf("This argument is optional.\n");
		return (false);
	}
	return (true);
}


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

bool	is_in_int_range(char *str)
{
	long result;

	result = 0;
	while(*str)
	{
		result = result * 10 + (*str - '0');
		if(result > INT_MAX)
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
		if(*str < '0' || *str > '9')
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

int pre_check(int ac, char **av)
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

int	main(int ac, char **av)
{
	t_data	data;
	if (pre_check(ac, av) != 0)
		return (1);
	if (init_values(ac, av, &data) != 0)
		return (1);


	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:29:06 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/06 16:33:58 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10;
		result = result + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

// uint64_t	get_time(void)
// {
// 	struct timeval tv;

// 	if (gettimeofday(&tv, NULL))
// 		return (0);
// 	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
// }

// int ft_dynamic_usleep(useconds_t total_us)
// {
// 	uint64_t start;
// 	uint64_t target;
// 	uint64_t now;

// 	start = get_time();
// 	target = start + total_us / 1000;  // Target time in milliseconds
// 	while ((now = get_time()) < target)
// 	{
// 		if (target - now > 1)
// 			usleep((target - now) * 1000); // Sleep remaining time, converted back to microseconds
// 		else
// 			usleep(1000); // Final adjustment for less than 1 millisecond left
// 	}

// 	return 0;
// }

// int main(void)
// {
// 	uint64_t	start_time;
// 	uint64_t	end_time;

// 	start_time = get_time();
// 	printf("Start time: %llu\n", start_time);
// 	ft_dynamic_usleep(10000);
// 	end_time = get_time();
// 	printf("End time: %llu\n", end_time);

// 	printf("Time took: %llu ms\n", end_time - start_time);
// 	return 0;
// }

// int value = 0;
// pthread_mutex_t lock;


// void* routine()
// {
// 	int i = 0;
// 	while (i < 10000000) {
// 		pthread_mutex_lock(&lock);
// 		value++;

// 		i++;
// 				pthread_mutex_unlock(&lock);
// 	}

// 	// for (int i = 0; i < 10000000; i++) {
// 	// 	value++;
// 	// }


// 	// printf("Routine running - 1\n");
// 	// sleep(1);
// 	// printf("Routine running - 2\n");
// 	return NULL;
// }

// int	main()
// {
// 	pthread_t tr1;
// 	pthread_t tr2;
// 	pthread_mutex_init(&lock, NULL);

// 	pthread_create(&tr1, NULL, routine, NULL);
// 	pthread_create(&tr2, NULL, routine, NULL);

// 	// printf("Main thread running\n");

// 	pthread_join(tr1, NULL);
// 	pthread_join(tr2, NULL);
// 	printf("Value: %d\n", value);
// 	// printf("Main thread running - 2\n");
// 	printf("Threads are done.\n");
// 	pthread_mutex_destroy(&lock);
// 	return 0;
// }

// void* routine()
// {
// 	printf("Routine running...");
// }

void	instructions()
{
	printf("Incorrect amount of arguments!\n");
	printf("You have to provide: ");
	printf("number_of_philosophers time_to_die time_to_eat time_to_sleep ");
	printf("number_of_times_each_philosopher_must_eat(optional).\n");
}

void	initialize(t_data *data)
{
	data->tid = NULL;
	data->num_of_philos = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
}

void parse_input_data(t_data *data, int ac, char **av)
{
	data->num_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6) {
		data->num_of_meals_required = ft_atoi(av[5]);
	}
}
int	main(int ac, char **av)
{

	t_data data;
	initialize(&data);

	if(ac != 5 && ac != 6)
	{
		instructions();
		return (1);
	}
	else
	{
		parse_input_data(&data, ac, av);

	}
	printf("Number of Philosophers: %d\n", data.num_of_philos);
	printf("Time to Die: %d milliseconds\n", data.time_to_die);
	printf("Time to Eat: %d milliseconds\n", data.time_to_eat);
	printf("Time to Sleep: %d milliseconds\n", data.time_to_sleep);
	printf("Number of Times Each Philosopher Must Eat: %d\n", data.num_of_meals_required);

	return (0);
}

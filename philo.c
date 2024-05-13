/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:29:06 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/13 14:58:52 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	// printf("FULL: %llu\n", (tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
	// printf("FIRST HALF: %llu\n", tv.tv_sec * (uint64_t)1000);
	// printf("LEFT OVER: %d\n", tv.tv_usec / 1000);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	*routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	usleep(10000);
	int i = 0;
	while(i < 5)
	{
		printf("Hello, this is philo: %d\n", philo->id);
		i++;
	}


	return (NULL);
}

int	start_threads(t_data *data)
{
	int i;

	i = -1;
	printf("TIME: %llu\n", get_time());
	while (++i < data->numb_of_philos)
	{
		if(pthread_create(&data->philos[i].thread_id, NULL, routine, &data->philos[i]) != 0)
		{
			return (1);
		}

	}
	printf("\n");
	printf("Philo created\n");
	printf("\n");
	// usleep(1000000);
	return (0);
}

//--------------------------------------------------------------

void	cleanup(t_data *data)
{
	int i;

	i = 0;
	while(i < data->numb_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->philos);
	pthread_mutex_destroy(&data->write);
}

int	init_philos(t_data *data)
{
	int i;

	i = -1;
	while(++i <data->numb_of_philos)
	{
		data->philos[i].id = i;
		data->philos[i].eat_count = 0;
		data->philos[i].is_eating = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].thread_id = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->numb_of_philos];
	}
	return (0);
}

int	init_forks(t_data *data)
{
	int i;

	i = -1;
	while(++i < data->numb_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
	}
	return (0);
}

int	dining_init(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->numb_of_philos);
	if (!(data->forks))
		return (1);
	if (init_forks(data) != 0)
	{
		free(data->forks);
		return (1);
	}
	data->philos = malloc(sizeof(t_philo) * data->numb_of_philos);
	if (!(data->philos))
	{
		free(data->forks);
		return (1);
	}
	init_philos(data);
	if (pthread_mutex_init(&data->write, NULL) != 0)
	{
		free(data->forks);
		free(data->philos);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	if (pre_check(ac, av) != 0)
		return (1);
	if (init_values(ac, av, &data) != 0)
		return (1);
	if (dining_init(&data) != 0)
		return (1);
	if (start_threads(&data) != 0)
		return (1);

	//TODO: Move this to seperate function.
	int i = -1;
	while(++i < data.numb_of_philos)
		pthread_join(data.philos[i].thread_id, NULL);

	cleanup(&data);
	return (0);
}


// 1. Start dining simulation
//

// tok = malloc( sizeof( char ) * ( strlen(tc) + 1 ) );

// if( tok == NULL )
// {
//      /* Malloc failed, deal with it */
// }

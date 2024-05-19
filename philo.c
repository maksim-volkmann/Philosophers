#include "philo.h"



void	print_log(t_philo *philo, const char *message)
{
	pthread_mutex_lock(&philo->data->write);
	if (!philo->data->died && !philo->data->all_ate)
	{
		printf("%llu %d %s\n", get_time() - philo->data->start_time, philo->id, message);
	}
	pthread_mutex_unlock(&philo->data->write);
}

void	single_philo(t_philo *philo)
{
		pthread_mutex_lock(philo->left_fork);
		print_log(philo, "has taken a fork");

		while (!philo->data->died)
			usleep(100);

		pthread_mutex_unlock(philo->left_fork);
}

bool	check_status(t_philo *philo)
{
	bool	result;

	pthread_mutex_lock(&philo->data->all_ate_mutex);
	result = !(philo->data->died || philo->data->all_ate);
	pthread_mutex_unlock(&philo->data->all_ate_mutex);

	return result;
}

void philo_eat(t_philo *philo)
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

void philo_sleep(t_philo *philo)
{
	print_log(philo, "is sleeping");
	simulate_action(philo->data->time_to_sleep);
}

void philo_think(t_philo *philo)
{
	print_log(philo, "is thinking");
}

void *routine(void *arg)
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

// void *routine(void *arg)
// {
// 	t_philo *philo = (t_philo *)arg;

// 	if (philo->data->numb_of_philos == 1)
// 	{
// 		single_philo(philo);
// 		return NULL;
// 	}

// 	while (check_status(philo))
// 	{
// 		if (philo->id % 2 == 0)
// 			usleep(100);

// 		//eating starts
// 		pthread_mutex_lock(philo->left_fork);
// 		print_log(philo, "has taken a fork");

// 		pthread_mutex_lock(philo->right_fork);
// 		print_log(philo, "has taken a fork");

// 		print_log(philo, "is eating");
// 		precise_sleep(philo->data->time_to_eat);


// 		pthread_mutex_lock(&philo->mutex_last_meal);
// 		philo->last_meal_time = get_time();
// 		philo->eat_count++;
// 		pthread_mutex_unlock(&philo->mutex_last_meal);

// 		pthread_mutex_unlock(philo->right_fork);
// 		pthread_mutex_unlock(philo->left_fork);
// 		//eating ends

// 		//sleeping starts
// 		print_log(philo, "is sleeping");
// 		precise_sleep(philo->data->time_to_sleep);
// 		//sleeping ends

// 		//thinking starts
// 		print_log(philo, "is thinking");
// 		//thinking ends
// 	}

// 	return NULL;
// }




void	*monitor(void *arg)
{
	t_data *data;
	int i;

	data = (t_data *)arg;
	while (!data->died && !data->all_ate)
	{
		i = 0;
		while (i < data->numb_of_philos)
		{
			pthread_mutex_lock(&data->philos[i].philo_lock);
			if (get_time() - data->philos[i].last_meal_time > data->time_to_die)
			{
				pthread_mutex_lock(&data->write);
				printf("%llu %d died\n", get_time() - data->start_time, data->philos[i].id);
				data->died = true;
				pthread_mutex_unlock(&data->write);
				pthread_mutex_unlock(&data->philos[i].philo_lock);
				return NULL;
			}
			pthread_mutex_unlock(&data->philos[i].philo_lock);
			i++;
		}
		usleep(100);
	}
	return NULL;
}



void	*waiter(void *arg)
{
	t_data *data;
	int all_ate;
	int i;

	data = (t_data *)arg;
	while (!data->died && !data->all_ate)
	{
		all_ate = 1;
		i = 0;
		while (i < data->numb_of_philos)
		{
			pthread_mutex_lock(&data->philos[i].philo_lock);
			if (data->philos[i].eat_count < data->number_of_meals)
			{
				all_ate = 0;
				pthread_mutex_unlock(&data->philos[i].philo_lock);
				break;
			}
			pthread_mutex_unlock(&data->philos[i].philo_lock);
			i++;
		}
		if (all_ate)
		{
			pthread_mutex_lock(&data->write);
			data->all_ate = true;
			pthread_mutex_unlock(&data->write);
		}
		usleep(100);
	}
	return NULL;
}


int	init_philos(t_data *data)
{
	int i;

	i = 0;
	while (i < data->numb_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].data = data;
		data->philos[i].last_meal_time = get_time();
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->numb_of_philos];
		pthread_mutex_init(&data->philos[i].philo_lock, NULL);
		i++;
	}
	return 0;
}

void	cleanup(t_data *data)
{
	int i;

	i = 0;
	while (i < data->numb_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].philo_lock);
		i++;
	}
	free(data->forks);
	free(data->philos);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->all_ate_mutex);
}

int	init_forks(t_data *data)
{
	int i;

	i = 0;
	while (i < data->numb_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			return 1;
		}
		i++;
	}
	return (0);
}

int	dining_init(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->numb_of_philos);
	if (!data->forks)
	{
		return 1;
	}

	if (init_forks(data) != 0)
	{
		free(data->forks);
		return 1;
	}

	data->philos = malloc(sizeof(t_philo) * data->numb_of_philos);
	if (!data->philos)
	{
		free(data->forks);
		return 1;
	}

	init_philos(data);

	if (pthread_mutex_init(&data->write, NULL) != 0)
	{
		free(data->forks);
		free(data->philos);
		return 1;
	}

	if (pthread_mutex_init(&data->all_ate_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->write);
		free(data->forks);
		free(data->philos);
		return 1;
	}

	return (0);
}


int	start_threads(t_data *data)
{
	data->start_time = get_time();
	if (pthread_create(&data->monitor_thread, NULL, monitor, data) != 0)
		return 1;

	if (data->number_of_meals > 0)
	{
		if (pthread_create(&data->waiter_thread, NULL, waiter, data) != 0)
			return 1;
	}

	int i;

	i = 0;
	while (i < data->numb_of_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, routine, &data->philos[i]) != 0)
			return 1;
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	t_data data;
	int i;

	if (pre_check(ac, av) != 0)
		return (1);
	if (init_values(ac, av, &data) != 0)
		return (1);
	if (dining_init(&data) != 0)
		return (1);
	if (start_threads(&data) != 0)
		return (1);
	pthread_join(data.monitor_thread, NULL);
	if (data.number_of_meals > 0)
		pthread_join(data.waiter_thread, NULL);
	i = 0;
	while (i < data.numb_of_philos)
	{
		pthread_join(data.philos[i].thread_id, NULL);
		i++;
	}
	cleanup(&data);
	return (0);
}

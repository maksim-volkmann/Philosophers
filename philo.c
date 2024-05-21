/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:24:03 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/21 10:54:44 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_log(philo, "has taken a fork");
	while (!get_died(philo->data))
		usleep(100);
	pthread_mutex_unlock(philo->l_fork);
}

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

void	*routine(void *arg)
{
	t_philo		*philo;
	uint64_t	time_to_think;

	philo = (t_philo *)arg;
	time_to_think = (philo->data->time_to_eat * 2) - philo->data->time_to_sleep;
	if (philo->data->numb_of_philos == 1)
	{
		single_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(10);
	while (!(check_died_status(philo) || check_all_ate_status(philo)))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo, time_to_think);
	}
	return (NULL);
}

void	*doctor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!(get_died(data) || get_all_ate(data)))
	{
		i = 0;
		while (i < data->numb_of_philos)
		{
			pthread_mutex_lock(&data->philos[i].mutex_last_meal);
			if (get_time() - data->philos[i].last_meal_time > data->time_to_die)
			{
				print_log(&data->philos[i], "died");
				set_died(data, true);
				pthread_mutex_unlock(&data->philos[i].mutex_last_meal);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philos[i].mutex_last_meal);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

bool	check_all_philos_ate(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numb_of_philos)
	{
		pthread_mutex_lock(&data->philos[i].mutex_last_meal);
		if (data->philos[i].eat_count < data->number_of_meals)
		{
			pthread_mutex_unlock(&data->philos[i].mutex_last_meal);
			return false;
		}
		pthread_mutex_unlock(&data->philos[i].mutex_last_meal);
		i++;
	}
	return true;
}

void	*waiter(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!(get_died(data) || get_all_ate(data)))
	{
		if (check_all_philos_ate(data))
			set_all_ate(data, true);
		usleep(1000);
	}
	return (NULL);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numb_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].mutex_last_meal);
		i++;
	}
	free(data->forks);
	free(data->philos);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->died_mutex);
	pthread_mutex_destroy(&data->all_ate_mutex);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numb_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].last_meal_time = get_time();
		data->philos[i].thread_id = 0;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->numb_of_philos];
		pthread_mutex_init(&data->philos[i].mutex_last_meal, NULL);
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numb_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	dining_init(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->numb_of_philos);
	if (!data->forks)
		return (1);
	if (init_forks(data) != 0)
	{
		free(data->forks);
		return (1);
	}
	data->philos = malloc(sizeof(t_philo) * data->numb_of_philos);
	if (!data->philos)
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
	if (pthread_mutex_init(&data->died_mutex, NULL) != 0
		|| pthread_mutex_init(&data->all_ate_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->write);
		free(data->forks);
		free(data->philos);
		return (1);
	}
	return (0);
}

int	start_threads(t_data *data)
{
	int	i;

	data->start_time = get_time();
	if (pthread_create(&data->doctor_thread, NULL, doctor, data) != 0)
		return (1);
	if (data->number_of_meals > 0)
	{
		if (pthread_create(&data->waiter_thread, NULL, waiter, data) != 0)
			return (1);
	}
	i = 0;
	while (i < data->numb_of_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL,
				routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_join(data->doctor_thread, NULL);
	if (data->number_of_meals > 0)
		pthread_join(data->waiter_thread, NULL);
	while (i < data->numb_of_philos)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (pre_check(ac, av) != 0)
		return (1);
	if (parse_init_values(ac, av, &data) != 0)
		return (1);
	additional_init(&data);
	if (dining_init(&data) != 0)
		return (1);
	if (start_threads(&data) != 0)
		return (1);
	join_threads(&data);
	cleanup(&data);
	return (0);
}

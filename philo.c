
#include "philo.h"


uint64_t get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void precise_sleep(uint64_t duration_ms)
{
	uint64_t start_time = get_time();
	while (get_time() - start_time < duration_ms)
	{
		usleep(100);
	}
}

void print_log(t_philo *philo, const char *message)
{
	pthread_mutex_lock(&philo->data->write);
	if (!philo->data->died)
	{
		printf("%llu %d %s\n", get_time() - philo->data->start_time, philo->id, message);
	}
	pthread_mutex_unlock(&philo->data->write);
}

// void	*routine(void *arg)
// {
// 	t_philo	*philo = (t_philo *)arg;

// 	// The philosophers alternatively eat, think, or sleep.
// 	//TODO: EAT \ SLEEP \ THINK function. Print correct messages:
// 	// ◦ timestamp_in_ms X has taken a fork
// 	// ◦ timestamp_in_ms X is eating
// 	// ◦ timestamp_in_ms X is sleeping
// 	// ◦ timestamp_in_ms X is thinking
// 	// ◦ timestamp_in_ms X died

// 	//1. EAT. Take forks (think about deadlock). simulate eating. drop forks.
// 	//2. SLEEP. simulate sleep.
// 	//3. THINK. not sure about this, have to wait until the forks are ready?
// 	// usleep(10000);
// 	// int i = 0;
// 	// printf("TIME in routine: %d\n", (get_time()) - (philo->data->start_time));
// 	// printf("TIME in routine: %llu\n", (get_time()) - philo->data->start_time);
// 	// printf("EATING: %llu\n", (get_time()) - philo->data->start_time + philo->data->time_to_eat);
// 	// printf("Time in routine: %llu\n", philo->data);
// 	// while(i < 2)
// 	// {
// 	// 	printf("Hello, this is philo: %d\n", philo->id);
// 	// 	i++;
// 	// }
// while (1)
//     {
// 		// if (philo->id % 2 != 0)
//         // {
//         //     precise_sleep(10);
//         // }
//         // Take forks
//         if (philo->id % 2 == 0)
//         {
//             pthread_mutex_lock(philo->left_fork);
//             print_log(philo, "has taken a fork");
//             pthread_mutex_lock(philo->right_fork);
//             print_log(philo, "has taken a fork");
//         }
//         else
//         {
//             pthread_mutex_lock(philo->right_fork);
//             print_log(philo, "has taken a fork");
//             pthread_mutex_lock(philo->left_fork);
//             print_log(philo, "has taken a fork");
//         }

//         // Eat
//         print_log(philo, "is eating");
//         precise_sleep(philo->data->time_to_eat);  // Simulate eating

//         // Drop forks
//         pthread_mutex_unlock(philo->left_fork);
//         pthread_mutex_unlock(philo->right_fork);

//         // Sleep
//         print_log(philo, "is sleeping");
//         precise_sleep(philo->data->time_to_sleep);  // Simulate sleeping

//         // Think
//         print_log(philo, "is thinking");
//     }


// 	return (NULL);
// }

void	ft_usleep(uint64_t sleep_time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < sleep_time)
		usleep(500);
}
// ft_usleep(philo->data->eat_time - 10);

// void	*routine(void *arg)
// {
// 	t_philo	*philo = (t_philo *)arg;

// 	if (philo->id % 2 == 0)
// 	{
// 		ft_usleep(philo->data->time_to_eat - 10);
// 	}


// 	while (1)
// 	{

// 		pthread_mutex_lock(philo->right_fork);
// 		print_log(philo, "has taken a fork");
// 		pthread_mutex_lock(philo->left_fork);
// 		print_log(philo, "has taken a fork");

// 		// Eat
// 		print_log(philo, "is eating");
// 		precise_sleep(philo->data->time_to_eat);  // Simulate eating

// 		// Drop forks
// 		pthread_mutex_unlock(philo->left_fork);
// 		pthread_mutex_unlock(philo->right_fork);

// 		// Sleep
// 		print_log(philo, "is sleeping");
// 		precise_sleep(philo->data->time_to_sleep);  // Simulate sleeping

// 		// Think
// 		print_log(philo, "is thinking");
// 		// usleep(1);
// 	}


// 	return (NULL);
// }


void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {

        if (philo->id % 2 == 0)
            usleep(100);

        pthread_mutex_lock(philo->left_fork);
        print_log(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_log(philo, "has taken a fork");

        // Eating
        print_log(philo, "is eating");
        precise_sleep(philo->data->time_to_eat);

        // Drop forks
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        // Sleeping
        print_log(philo, "is sleeping");
        precise_sleep(philo->data->time_to_sleep);

        // Thinking
        print_log(philo, "is thinking");
    }
    return (NULL);
}




// void *routine(void *arg)
// {
// 	t_philo *philo = (t_philo *)arg;

// 	pthread_mutex_t *first_fork = philo->id % 2 == 0 ? philo->left_fork : philo->right_fork;
// 	pthread_mutex_t *second_fork = philo->id % 2 == 0 ? philo->right_fork : philo->left_fork;

// 	while (1)
// 	{
// 		// Take forks
// 		pthread_mutex_lock(first_fork);
// 		print_log(philo, "has taken a fork");

// 		pthread_mutex_lock(second_fork);
// 		print_log(philo, "has taken a fork");
// 		// Eat
// 		print_log(philo, "is eating");
// 		philo->last_meal_time = get_time();

// 		precise_sleep(philo->data->time_to_eat);  // Simulate eating
// 		philo->eat_count++;
// 		// Drop forks

// 		pthread_mutex_unlock(first_fork);
// 		pthread_mutex_unlock(second_fork);
// 		// Sleep

// 		print_log(philo, "is sleeping");
// 		precise_sleep(philo->data->time_to_sleep);  // Simulate sleeping
// 		// Think
// 		print_log(philo, "is thinking");
// 	}
// 	return (NULL);
// }


int	start_threads(t_data *data)
{
	int i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->numb_of_philos)
	{
		if(pthread_create(&data->philos[i].thread_id, NULL, routine, &data->philos[i]) != 0)
		{
			return (1);
		}

	}
	// usleep(1000000);
	// printf("TIME AFTER: %llu\n", get_time() - (data->start_time));
	// printf("\n");
	// printf("Philo created\n");
	// printf("\n");
	// usleep(1000000);
	return (0);
}

//--------------------------------------------------------------

void	cleanup(t_data *data)
{
	int i;

	i = 0;
	while (i < data->numb_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->philos);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->fork_mutex); // Destroy the fork control mutex
}

int init_philos(t_data *data)
{
    int i;

    i = 0;
    while (i < data->numb_of_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].eat_count = 0;
        data->philos[i].is_eating = 0;
        data->philos[i].data = data;
        data->philos[i].last_meal_time = 0;
        data->philos[i].thread_id = 0;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->numb_of_philos];
        i++;
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

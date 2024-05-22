/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:24:03 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/22 16:50:38 by mvolkman         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_data	data;

	if (pre_check(ac, av) != 0)
		return (1);
	if (parse_init_values(ac, av, &data) != 0)
		return (1);
	additional_init(&data);
	if (dining_init(&data) != 0)
	{
		cleanup(&data);
		return (1);
	}
	if (start_threads(&data) != 0)
	{
		cleanup(&data);
		return (1);
	}
	join_threads(&data);
	cleanup(&data);
	return (0);
}

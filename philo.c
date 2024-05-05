/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:29:06 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/05 16:57:09 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h> // for sleep function
#include <stdint.h>  // For uint64_t


uint64_t	get_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

int ft_dynamic_usleep(useconds_t total_us)
{
	uint64_t start;
	uint64_t target;
	uint64_t now;

	start = get_time();
	target = start + total_us / 1000;  // Target time in milliseconds
	while ((now = get_time()) < target)
	{
		if (target - now > 1)
			usleep((target - now) * 1000); // Sleep remaining time, converted back to microseconds
		else
			usleep(1000); // Final adjustment for less than 1 millisecond left
	}

	return 0;
}

int main(void)
{
	uint64_t	start_time;
	uint64_t	end_time;

	start_time = get_time();
	printf("Start time: %llu\n", start_time);
	ft_dynamic_usleep(10000);
	end_time = get_time();
	printf("End time: %llu\n", end_time);

	printf("Time took: %llu ms\n", end_time - start_time);
	return 0;
}

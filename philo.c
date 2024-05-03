/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:29:06 by mvolkman          #+#    #+#             */
/*   Updated: 2024/05/03 15:02:10 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h> // for sleep function

int main() {
    struct timeval tv; // Declare a variable of type struct timeval

    // Get the current time
    gettimeofday(&tv, NULL);

    // Convert seconds to milliseconds
    long milliseconds_from_seconds = tv.tv_sec * 1000;

    // Add milliseconds from microseconds
    long milliseconds_from_microseconds = (tv.tv_usec / 1000);

    // Add milliseconds from seconds and microseconds
    long total_milliseconds = milliseconds_from_seconds + milliseconds_from_microseconds;

    printf("Current time in milliseconds (from seconds): %ld\n", milliseconds_from_seconds);
    printf("Current time in milliseconds (from microseconds): %ld\n", total_milliseconds);

    return 0;
}

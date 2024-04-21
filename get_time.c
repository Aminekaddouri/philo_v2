/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 08:08:21 by kaddouri          #+#    #+#             */
/*   Updated: 2024/04/19 02:08:58 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	t_time	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

long long	elapsed_time(t_philo *philo)
{
	long long	time;

	time = get_time() - philo->data->start_time;
	return (time);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
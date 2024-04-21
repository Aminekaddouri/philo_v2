/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 09:59:07 by kaddouri          #+#    #+#             */
/*   Updated: 2024/04/21 04:25:14 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_and_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
		pthread_join(data->philo[i++].thread, NULL);
	pthread_join(data->monitor_all_ate, NULL);
	pthread_join(data->monitor_died, NULL);
	free(data->philo);
	i = 0;
	while (i < data->num_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->last_meal_lock);
	pthread_mutex_destroy(&data->all_ate_lock);
	pthread_mutex_destroy(&data->finish_lock);
	free(data->forks);
	free(data);
}

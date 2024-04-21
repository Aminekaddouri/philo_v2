/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philosopher.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 08:05:54 by kaddouri          #+#    #+#             */
/*   Updated: 2024/04/21 04:25:05 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_if_died(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (true)
	{
		pthread_mutex_lock(&data->finish_lock);
		if (data->finish_simulation)
		{
			pthread_mutex_unlock(&data->finish_lock);
			break ;
		}
		pthread_mutex_unlock(&data->finish_lock);
		i = 0;
		while (i < data->num_philo)
		{
			pthread_mutex_lock(&data->last_meal_lock);
			if ((data->philo[i].last_meal + data->time_to_die) < get_time())
			{
				print_message(&data->philo[i], "died");
				data->philo[i].should_die = true;
				// pthread_mutex_lock(&data->finish_lock);
				data->finish_simulation = true;
				// pthread_mutex_unlock(&data->finish_lock);
			}
			pthread_mutex_unlock(&data->last_meal_lock);
			i++;
		}
		ft_usleep(10);
	}
	return (NULL);
}

void	*check_if_all_ate(void *arg)
{
	t_data	*data;

	data = arg;
	while (true)
	{
		pthread_mutex_lock(&data->finish_lock);
		if (data->finish_simulation)
		{
			pthread_mutex_unlock(&data->finish_lock);
			break ;
		}
		pthread_mutex_unlock(&data->finish_lock);
		pthread_mutex_lock(&data->all_ate_lock);
		if (data->all_ate == data->num_philo)
		{
			// pthread_mutex_lock(&data->finish_lock);
			data->finish_simulation = true;
			// pthread_mutex_unlock(&data->finish_lock);
		}
		pthread_mutex_unlock(&data->all_ate_lock);
		ft_usleep(10);
	}
	return (NULL);
}

void	ft_init_philo(t_philo *philo, int i, t_data *data)
{
	philo->id = i;
	philo->data = data;
	philo->last_meal = data->start_time;
	philo->should_die = false;
	philo->eat_count = 0;
}

int	initialize_philosopher(t_data *data)
{
	// pthread_t	monitor_died;
	// pthread_t	monitor_all_ate;
	int			i;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_philo)
	{
		ft_init_philo(&data->philo[i], i, data);
		if (pthread_create(&data->philo[i].thread, NULL, philosophers,
				&data->philo[i]) != 0)
			return (print_error("Failed to create the thread"));
		i++;
	}
	if (pthread_create(&data->monitor_died, NULL, check_if_died, data) != 0)
		return (print_error("Failed to create the thread"));
	// pthread_detach(monitor_died);
	if (data->num_each_must_eat > 0)
	{
		if (pthread_create(&data->monitor_all_ate, NULL, check_if_all_ate, data) != 0)
			return (print_error("Failed to create the thread"));
		// pthread_detach(monitor_all_ate);
	}
		
	return (SUCCESS);
}

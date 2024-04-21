/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 03:02:33 by kaddouri          #+#    #+#             */
/*   Updated: 2024/04/19 20:56:21 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_arguments(t_data *data, int ac, char **av)
{
	data->num_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->num_each_must_eat = ft_atoi(av[5]);
	else
		data->num_each_must_eat = -1;
}

int	parsing(t_data data, int ac)
{
	if (ac == 6 && data.num_each_must_eat <= 0)
		return (print_error("ERROR: wrong num of meals must eat\n"));
	if (data.num_philo <= 0 || data.num_philo > 200)
		return (print_error("ERROR: wrong num of philo\n"));
	if (data.time_to_die < 60)
		return (print_error("ERROR: wrong time to die\n"));
	if (data.time_to_eat < 60)
		return (print_error("ERROR: wrong time to eat\n"));
	if (data.time_to_sleep < 60)
		return (print_error("ERROR: wrong time to sleep\n"));
	return (SUCCESS);
}

int	initialize_mutex(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (print_error("Failed to initialize the mutex"));
	if (pthread_mutex_init(&data->last_meal_lock, NULL) != 0)
		return (print_error("Failed to initialize the mutex"));
	if (pthread_mutex_init(&data->all_ate_lock, NULL) != 0)
		return (print_error("Failed to initialize the mutex"));
	if (pthread_mutex_init(&data->finish_lock, NULL) != 0)
		return (print_error("Failed to initialize the mutex"));
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (print_error("Failed to initialize the mutex"));
		i++;
	}
	return (SUCCESS);
}

int	init_data(t_data *data, int ac, char **av)
{
	initialize_arguments(data, ac, av);
	if (parsing(*data, ac))
		return (FAILURE);
	data->philo = ft_malloc(sizeof(t_philo) * data->num_philo);
	data->forks = ft_malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->philo || !data->forks)
		return (print_error("Malloc Error!\n"));
	data->finish_simulation = false;
	data->all_ate = 0;
	if (initialize_mutex(data))
		return (FAILURE);
	if (initialize_philosopher(data))
		return (FAILURE);
	return (SUCCESS);
}

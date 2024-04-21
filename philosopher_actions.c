/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 08:51:05 by kaddouri          #+#    #+#             */
/*   Updated: 2024/04/21 04:25:24 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_grap_fork(t_philo *philo, int fork)
{
	pthread_mutex_lock(&philo->data->forks[fork]);
	print_message(philo, "has taken a fork");
}

void	philo_is_eating(t_philo *philo)
{
	print_message(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->last_meal_lock);
	philo->last_meal = get_time();
	philo->eat_count++;
	if (philo->eat_count == philo->data->num_each_must_eat)
	{
		pthread_mutex_lock(&philo->data->all_ate_lock);
		philo->data->all_ate++;
		pthread_mutex_unlock(&philo->data->all_ate_lock);
	}
	pthread_mutex_unlock(&philo->data->last_meal_lock);
}

void	philo_put_fork(t_philo *philo, int right_fork, int left_fork)
{
	pthread_mutex_unlock(&philo->data->forks[right_fork]);
	pthread_mutex_unlock(&philo->data->forks[left_fork]);
}

void	sleep_then_think(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
	print_message(philo, "is thinking");
}

void	*philosophers(void *arg)
{
	t_philo	*philo;
	int		left_fork;
	int		right_fork;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(60);
	while (true)
	{
		pthread_mutex_lock(&philo->data->finish_lock);
		if (philo->should_die || philo->data->finish_simulation)
		{
			pthread_mutex_unlock(&philo->data->finish_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->finish_lock);
		right_fork = philo->id;
		left_fork = (philo->id + 1) % philo->data->num_philo;
		philo_grap_fork(philo, right_fork);
		if (philo->data->num_philo == 1)
		{
			ft_usleep(100);
			break ;
		}
		philo_grap_fork(philo, left_fork);
		philo_is_eating(philo);
		philo_put_fork(philo, right_fork, left_fork);
		sleep_then_think(philo);
	}
	return (NULL);
}

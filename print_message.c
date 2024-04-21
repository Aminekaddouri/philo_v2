/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaddour <akaddour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 08:34:13 by kaddouri          #+#    #+#             */
/*   Updated: 2024/04/19 22:41:26 by akaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->finish_lock);
	if (philo->data->finish_simulation)
	{
		pthread_mutex_unlock(&philo->data->finish_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->finish_lock);
	pthread_mutex_lock(&philo->data->print_lock);
		printf("%lli\t%i\t%s\n", elapsed_time(philo), philo->id + 1, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
}

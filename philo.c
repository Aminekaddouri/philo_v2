/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaddouri <kaddouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:11:43 by kaddouri          #+#    #+#             */
/*   Updated: 2024/03/22 14:00:41 by kaddouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 5 && ac != 6)
		return (print_error("Error! incorrect number of arguments\n"));
	data = ft_malloc(sizeof(t_data));
	if (!data)
		return (print_error("Malloc Error!"));
	if (init_data(data, ac, av) == SUCCESS)
	{
		join_and_destroy(data);
		return (SUCCESS);
	}
	return (FAILURE);
}

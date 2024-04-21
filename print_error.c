/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaddouri <kaddouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:37:49 by kaddouri          #+#    #+#             */
/*   Updated: 2024/03/21 10:25:51 by kaddouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *err)
{
	write(STDERR_FILENO, err, ft_strlen(err));
	return (FAILURE);
}

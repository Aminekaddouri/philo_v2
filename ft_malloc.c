/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaddouri <kaddouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:58:37 by kaddouri          #+#    #+#             */
/*   Updated: 2024/03/21 07:55:29 by kaddouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_malloc(size_t size)
{
	void	*alloc;

	alloc = malloc(size);
	if (!alloc)
		return (0);
	return (alloc);
}

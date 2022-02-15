/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 11:43:50 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/02/15 10:40:24 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_check(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\v'
		|| nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == ' ')
		i++;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;
	int	sign;
	int	k;

	n = 0;
	k = 0;
	sign = 1;
	i = ft_check(nptr);
	while (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		k++;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = n * 10 + (nptr[i] - 48);
		i++;
	}
	if (k > 1)
		return (0);
	return (n * sign);
}

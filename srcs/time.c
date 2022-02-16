/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:43:21 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/02/16 16:33:56 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_time(t_param *param)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	param->first_time = t.tv_sec * 1000 + t.tv_usec / 1000;
}

long int	past_time(long int start_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + time.tv_usec / 1000) - start_time);
}

void	ft_usleep(int duration)
{
	long int	start;
	long int	current;

	start = past_time(0);
	current = start;
	while (duration > current - start)
	{
		usleep(100);
		current = past_time(0);
	}
}

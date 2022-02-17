/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:47:26 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/02/17 11:28:13 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	stop_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->prm->mutex_death);
	philo->prm->is_die = 1;
	pthread_mutex_unlock(&philo->prm->mutex_death);
	pthread_mutex_unlock(&philo->prm->mutex_eat);
	return (1);
}

int	is_die(t_philo *philo)
{
	print_status("is dead", philo);
	pthread_mutex_lock(&philo->prm->mutex_death);
	philo->prm->is_die = 1;
	pthread_mutex_unlock(&philo->prm->mutex_death);
	pthread_mutex_unlock(&philo->prm->mutex_eat);
	return (1);
}

void	is_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->prm->mutex_death);
	philo->prm->is_die = 0;
	pthread_mutex_unlock(&philo->prm->mutex_death);
}

int	check_death(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->prm->nb_philo)
	{
		pthread_mutex_lock(&philo->prm->mutex_eat);
		if (philo[i].ph_eat == philo->prm->nb_eat && philo[i].done_eat == 0)
		{
			pthread_mutex_lock(&philo->prm->mutex_done);
			philo[i].done_eat = 1;
			pthread_mutex_unlock(&philo->prm->mutex_done);
			philo->prm->everyone++;
			if (philo->prm->everyone == philo->prm->nb_philo)
				return (stop_eating(philo));
		}
		if (past_time(philo->prm->first_time) - philo[i].last_eat \
			> philo->prm->time_to_die)
			return (is_die(philo));
		else
			is_alive(philo);
		pthread_mutex_unlock(&philo->prm->mutex_eat);
	}
	return (0);
}

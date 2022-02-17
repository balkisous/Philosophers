/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:18:33 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/02/17 11:16:33 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	return_unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (1);
}

int	execute_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);
	if (print_status("has taken a fork", philo))
		return (pthread_mutex_unlock(&philo->r_fork), 1);
	pthread_mutex_lock(philo->l_fork);
	if (print_status("has taken a fork", philo))
		return (return_unlock(philo));
	pthread_mutex_lock(&philo->prm->mutex_eat);
	philo->last_eat = past_time(philo->prm->first_time);
	philo->ph_eat++;
	pthread_mutex_unlock(&philo->prm->mutex_eat);
	if (print_status("is eating", philo))
		return (return_unlock(philo));
	ft_usleep(philo->prm->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
	if (print_status("is sleeping", philo))
		return (1);
	ft_usleep(philo->prm->time_to_sleep);
	if (print_status("is thinking", philo))
		return (1);
	return (0);
}
//make his days actions

int	print_status(char *action, t_philo *philo)
{
	long int	time;
	int			death;
	int			done;

	pthread_mutex_lock(&philo->prm->mutex_death);
	death = philo->prm->is_die;
	pthread_mutex_unlock(&philo->prm->mutex_death);
	if (death)
		return (1);
	pthread_mutex_lock(&philo->prm->mutex_done);
	done = philo->done_eat;
	pthread_mutex_unlock(&philo->prm->mutex_done);
	time = past_time(philo->prm->first_time);
	if (time >= 0 && time <= 2147483647 && done == 0)
	{
		printf("%ldms %d %s\n", time, philo->id, action);
	}
	return (0);
}
//print his action

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 09:18:33 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/02/16 16:44:57 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	execute_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);
	print_status("has taken a fork", philo);
	pthread_mutex_lock(philo->l_fork);
	print_status("has taken a fork", philo);
	pthread_mutex_lock(&philo->prm->mutex_eat);
	philo->last_eat = past_time(philo->prm->first_time);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->prm->mutex_eat);
	print_status("is eating", philo);
	ft_usleep(philo->prm->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
	print_status("is sleeping", philo);
	ft_usleep(philo->prm->time_to_sleep);
	print_status("is thinking", philo);
}
//make his days actions

void	print_status(char *action, t_philo *philo)
{
	long int	time;
	int			death;

	pthread_mutex_lock(&philo->prm->mutex_death);
	death = philo->prm->is_die;
	pthread_mutex_unlock(&philo->prm->mutex_death);
	if (death)
		return ;
	time = past_time(philo->prm->first_time);
	if (time >= 0 && time <= 2147483647)
	{
		printf("%ldms %d %s\n", time, philo->id, action);
	}
}
//print his action
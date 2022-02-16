/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:01:18 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/02/16 16:45:05 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	one_philo(t_philo *philo)
{
	printf("0ms 1 has taken a fork\n");
	ft_usleep(philo->prm->time_to_die);
	printf("%ims 1 is dead\n", philo->prm->time_to_die);
}
//for only one philo

void	*routine(void *ph)
{
	t_philo	*philo;
	int		death;

	philo = (t_philo *)(ph);
	pthread_mutex_lock(&philo->prm->mutex_death);
	death = philo->prm->is_die;
	pthread_mutex_unlock(&philo->prm->mutex_death);
	while (death == 0)
	{
		execute_routine(philo);
		pthread_mutex_lock(&philo->prm->mutex_death);
		death = philo->prm->is_die;
		pthread_mutex_unlock(&philo->prm->mutex_death);
	}
	return (0);
}
//check that everyone is alive and execute the routine

int	begin_my_philo(t_philo *philo, t_param *param)
{
	int	i;
	int	death;

	init_time(param);
	i = -1;
	while (++i < param->nb_philo)
	{
		if (i % 2 == 0)
			pthread_create(&philo[i].ph, NULL, routine, &philo[i]);
	}
	i = -1;
	ft_usleep(100);
	while (++i < param->nb_philo)
	{
		if (i % 2 != 0)
			pthread_create(&philo[i].ph, NULL, routine, &philo[i]);
	}
	while (42)
	{
		death = check_death(philo);
		if (death)
			break ;
	}
	return (0);
}
//create the threads and launch it
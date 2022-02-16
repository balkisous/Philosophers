/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:01:18 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/02/16 15:10:49 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	one_philo(t_philo *philo)
{
	print_status("taken a fork", philo);
	ft_usleep(philo->prm->time_to_die);
	printf("Philo number 1 die\n");
}

void	*routine(void *ph)
{
	t_philo *philo;
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

int	begin_my_philo(t_philo *philo, t_param *param)
{
	int	i;
	int	death;

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
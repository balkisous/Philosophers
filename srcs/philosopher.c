/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:01:18 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/02/16 11:37:17 by bben-yaa         ###   ########.fr       */
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

int	ft_launch_thread(t_philo *philo, int module)
{
	int		i;

	i = -1;
	while (++i < philo->prm->nb_philo)
	{
		if (philo[i].id % 2 == module)
		{
			printf("Je lance le thread pour le philo id %d et module %d\n", philo[i].id, module);
			if (pthread_create(&philo[i].ph, NULL, &routine, &philo[i]) != 0)
			{
				printf("problem encountered when creating threads\n");
				return (0);
			}
		}
	}
	return (1);
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
	(void)death;
	/*while (42)
	{
		death = check_death(philo);
		if (death)
			break ;
	}*/
	printf("here before return 0\n");
	return (0);
}
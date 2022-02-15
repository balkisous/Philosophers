/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balkis <balkis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:01:18 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/02/15 20:42:56 by balkis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	one_philo(t_param *param)
{
	(void)param;
//	print_status("take his right fork", 1, param);
//	ft_sleep(param->time_to_die);
//	printf("Philo number 1 die\n");
}

void	*routine(void *ph)
{
	t_philo *philo;
	int		death;

	philo = (t_philo *)(ph);
	pthread_mutex_lock(&philo->prm->mutex_death);
	death = philo->prm->is_die;
	pthread_mutex_unlock(&philo->prm->mutex_death);
	printf("... passe\n");
	while (death == 0)
	{
		//start_routine(philo);
		pthread_mutex_lock(&philo->prm->mutex_death);
		death = philo->prm->is_die;
		pthread_mutex_unlock(&philo->prm->mutex_death);
	}
	return (0);
}

int	ft_launch_thread(t_philo *philo, int module)
{
	int		i;

	i = 0;
	while (i < philo->prm->nb_philo)
	{
		printf("ici pour id %d\n", philo[i].id);
		if (philo[i].id % 2 == module)
		{
			if (pthread_create(&philo[i].ph, NULL, &routine, &philo[i]) != 0)
			{
				printf("problem encountered when creating threads\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	begin_my_philo(t_philo *philo)
{
	int	i;
	int	death;

	i = 0;
	if (!ft_launch_thread(philo, 0))
		return ;
	sleep(10);
	if (!ft_launch_thread(philo, 1))
		return ;
	(void)death;
	/*while (42)
	{
		death = check_death(philo);
		if (death)
			break ;
	}*/	
}
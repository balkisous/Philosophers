/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:29:58 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/02/17 09:34:38 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_philo(t_param *param, t_philo *philo)
{
	int	i;
	int	nb;

	i = 0;
	nb = param->nb_philo;
	while (i < nb)
	{
		philo[i].id = i + 1;
		pthread_mutex_init(&philo[i].r_fork, NULL);
		philo[i].prm = param;
		philo[i].last_eat = 0;
		philo[i].nb_eat = 0;
		i++;
	}
	i = 0;
	while (i < nb)
	{
		if (i == nb - 1)
			philo[i].l_fork = &philo[0].r_fork;
		else
			philo[i].l_fork = &philo[i + 1].r_fork;
		i++;
	}
}

void	destroy_mutex(t_param *param, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < param->nb_philo)
		pthread_mutex_destroy(&philo[i].r_fork);
	pthread_mutex_destroy(&param->mutex_death);
	pthread_mutex_destroy(&param->mutex_eat);
}

int	ft_join_thread(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->prm->nb_philo)
	{
		pthread_join(philo[i].ph, NULL);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_param	param;
	t_philo	*philo;

	if (!ft_parse_philo(argc, argv, &param))
		return (1);
	philo = malloc(sizeof(t_philo) * param.nb_philo);
	if (!philo)
		return (printf("Error, malloc fail\n"), 1);
	init_philo(&param, philo);
	if (param.nb_philo == 1)
	{
		one_philo(philo);
		destroy_mutex(&param, philo);
		free(philo);
		return (0);
	}	
	else
		begin_my_philo(philo, &param);
	if (ft_join_thread(philo))
		return (1);
	destroy_mutex(&param, philo);
	free(philo);
	return (0);
}

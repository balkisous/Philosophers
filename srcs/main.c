/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:29:58 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/02/16 11:41:48 by bben-yaa         ###   ########.fr       */
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
	pthread_mutex_destroy(&param->mutex_write);
	
}

int	main(int argc, char **argv)
{
	t_param param;
	t_philo *philo;
	int		i;

	i = -1;
	if (!ft_parse_philo(argc, argv, &param))
		return (1);
	philo = malloc(sizeof(t_philo) * param.nb_philo);
	if (!philo)
	{
		printf("Error, malloc\n");
		return (0);
	}
	init_philo(&param, philo);
	
	if (param.nb_philo == 1)
		one_philo(philo);
	else
		begin_my_philo(philo, &param);
	printf("we finish the program\n");
	destroy_mutex(&param, philo);
	while (++i < param.nb_philo)
		pthread_join(philo[i].ph, NULL);
	free(philo);
	printf("We finish to join\n");
	return (0);
}
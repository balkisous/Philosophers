/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 09:56:46 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/02/17 11:29:21 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_numeric(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (argv[j])
	{
		while (argv[j][i])
		{
			if (!((argv[j][i] >= '0' && argv[j][i] <= '9') \
				|| argv[j][i] == '-'))
				return (0);
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}
	//check that args are only numeric

void	init_param(t_param *param, char **argv)
{
	param->nb_philo = ft_atoi(argv[1]);
	param->time_to_die = ft_atoi(argv[2]);
	param->time_to_eat = ft_atoi(argv[3]);
	param->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		param->nb_eat = ft_atoi(argv[5]);
	else
		param->nb_eat = 2147483647;
	param->is_die = 0;
	param->everyone = 0;
	pthread_mutex_init(&(param->mutex_done), NULL);
	pthread_mutex_init(&(param->mutex_eat), NULL);
	pthread_mutex_init(&(param->mutex_death), NULL);
}
//init struct param

int	ft_parse_philo(int argc, char **argv, t_param *param)
{
	if (!(argc <= 6 && argc >= 5))
		return (printf("Error, not the right number of arguments\n"), 0);
	if (!is_numeric(argv))
		return (printf("Error, only numeric value are accepted\n"), 0);
	init_param(param, argv);
	if (param->nb_philo > 200)
		return (printf("Error, too many philos\n"), 0);
	if (param->nb_philo <= 0 || param->time_to_die <= 0 || \
		param->time_to_eat <= 0 || param->time_to_sleep <= 0 || \
		(argv[5] && param->nb_eat <= 0))
		return (printf("Error, arguments must be positive\n"), 0);
	return (1);
}

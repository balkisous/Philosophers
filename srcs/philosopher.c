/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:01:18 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/02/15 16:01:46 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	one_philo(t_param *param)
{
	print_status("take his right fork", 1, param);
	ft_sleep(param->time_to_die);
	printf("Philo number 1 die\n");
}
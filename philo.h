/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:31:27 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/02/16 11:37:28 by bben-yaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	pthread_t		ph;
	pthread_mutex_t	*l_fork;	
	pthread_mutex_t	r_fork;
	int				nb_eat;
	long 			last_eat;
	struct s_param	*prm;
}				t_philo;

typedef struct s_param
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	long				first_time;
	int					nb_eat;
	int					is_die;
	pthread_mutex_t		mutex_write;	
	pthread_mutex_t		mutex_eat;
	pthread_mutex_t		mutex_death;
		
}				t_param;

//main.c
void		init_philo(t_param *param, t_philo *philo);
void		destroy_mutex(t_param *param, t_philo *philo);

//parsing.c
int			is_numeric(char **argv);
void		init_param(t_param *param, char **argv);
int			ft_parse_philo(int argc, char **argv, t_param *param);

//philosopher.c
void	one_philo(t_philo *philo);
void	*routine(void *ph);
int		ft_launch_thread(t_philo *philo, int module);
int		begin_my_philo(t_philo *philo, t_param *param);

//routine.c
void	execute_routine(t_philo *philo);
void	print_status(char *action, t_philo *philo);

//atoi.c
int			ft_atoi(const char *nptr);

//time.c
void		init_time(t_param *param);
long int	past_time(long int start_time);
void		ft_usleep(int duration);


# endif
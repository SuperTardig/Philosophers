/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperron <bperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:43:09 by bperron           #+#    #+#             */
/*   Updated: 2022/07/27 10:14:21 by bperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define THINK 1
# define MAX_REP 4

typedef struct s_vars	t_vars;

typedef struct s_philo
{
	int			fork;
	int			status;
	int			nb_eat;
	int			philo_nb;
	long		last_eat;
	t_vars		*vars;
	pthread_t	thread;
}	t_philo;

typedef struct s_vars
{
	int					ttd;
	int					tte;
	int					tts;
	int					rep;
	int					status;
	int					nb_eat;
	int					nb_philo;
	long				begin_time;
	t_philo				*philos;
	pthread_mutex_t		msg;
	pthread_mutex_t		*forks;
	pthread_mutex_t		check;
}	t_vars;

long	ft_atol(char *str);
int		parsing(t_vars *vars, char **av, int ac);
void	print_msg(t_philo *philo, char *str);
long	get_time(void);
void	make_philos(t_vars *vars);
void	my_sleep(int ttw);

#endif
